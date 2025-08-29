"""
Learn API constraints from mistakes.

The API functions of a library require to be called with specific conventions.
For example, an API may allocate memory within its implementation, and the user
is expected to free the memory after use, which will cause a memory leak if not done.
These conventions are called API constraints, which are usually not documented.
When LLM generates code snippets, it may not follow these constraints, which will
cause ASan crashes. To avoid this, we need to learn these constraints from mistakes.
A reasonable methodology is:
-   Collect crashes from ASan. Normally LLM will be asked to fix the crash, but if
    the same crash happens repeatedly, it is assumed to be a constraint violation.
    The crash will be sent to the learner.
-   The learner will analyze the crash and extract detailed information about the crash.
    Useful information includes:
    -   The reason of the crash.
    -   The related API functions of the crash.
    -   The inner implementation of the API functions. If the implementation is too complex,
        it may be simplified.
-   Ask LLM to:
    -   Explain the root cause of the crash.
    -   Determine whether the crash is caused by a constraint violation. If so, write a short
        description of the constraint.
    -   Write the fixed code snippet.
-   Build and run the fixed code snippet. If the crash is fixed, the constraint description
    will be added to the comprehension database, and the fixed code snippet will update to
    the fuzz driver.
"""

from loguru import logger
from pathlib import Path
from typing import Callable
from dataclasses import dataclass
from enum import StrEnum, auto
import time

from .sanitizer import DriverRunAttempt
from .driver import FuzzDriver
from .scheduler import Scheduler
from src.analyzer.asan import AsanError
from src.analyzer.report import CrashReportComposer
from src.comprehender.comprehender import LibraryComprehension
from src.llm.llm import LLMClient, LLMChat, ReasoningLLMClient
from src.llm.prompter import CrashConstraintPrompter, CrashContraintReasoningPrompter
from src.preprocessor.information import InfoRepository
from src.preprocessor.api import APICollection
from src import vars as global_vars


class CrashRecorder:
    """
    Class to categorize and record crashes.
    """

    # The threshold of memory leak crashes to disable LeakSanitizer
    DISABLE_LEAK_SANITIZER_THRESHOLD = 3
    # Whether to save crashes to disk
    SAVE_CRASHES = True

    class LearningStatus(StrEnum):
        """
        The status of learning.
        """

        LEARNED = auto()
        """
        The crash has been learned.
        """

        LEARNING = auto()
        """
        The crash is being learned.
        """

        FAILED = auto()
        """
        The crash learning failed.
        """

        NOT_LEARNED = auto()
        """
        The crash is not learned.
        """

        NOT_NEEDED = auto()
        """
        The crash does not need to be learned.
        """

    @dataclass
    class RecordedCrash:
        """
        Class to record a crash.
        """

        signature: str
        """
        The crash signature which identifies the crash.
        """

        count: int
        """
        The crash count.
        """

        learning_status: "CrashRecorder.LearningStatus"
        """
        The learning status of the crash.
        """

        crashes: list[AsanError]
        """
        The ASan errors of the same crash.
        """

        @classmethod
        def from_empty(cls, signature: str) -> "CrashRecorder.RecordedCrash":
            """
            Create a RecordedCrash from an empty one.

            :param signature: The crash signature
            :return: The RecordedCrash
            """
            if "@unknown" in signature or "@driver" in signature:
                # driver crashes or unknown crashes do not need to be learned
                status = CrashRecorder.LearningStatus.NOT_NEEDED
            else:
                status = CrashRecorder.LearningStatus.NOT_LEARNED
            return cls(signature, 0, status, [])

    def __init__(self):
        """
        Initialize the crash recorder.
        """
        self.crashes: dict[str, CrashRecorder.RecordedCrash] = {}

    def record(self, asan_error: AsanError) -> "CrashRecorder.RecordedCrash":
        """
        record a crash.

        :param asan_error: The ASan error
        :return: The recorded crash
        """
        self.crashes.setdefault(
            asan_error.signature,
            CrashRecorder.RecordedCrash.from_empty(asan_error.signature),
        )
        self.crashes[asan_error.signature].count += 1
        self.crashes[asan_error.signature].crashes.append(asan_error)
        logger.debug(f"Recorded crash {asan_error.signature}")

        # save crash to tmp/crashes
        crash_path = Path(global_vars.library_config["output_path"]) / "tmp" / "crashes"
        crash_path.mkdir(parents=True, exist_ok=True)
        with open(
            crash_path / f"{asan_error.signature}_{int(time.time())}.log", "w"
        ) as f:
            f.write(asan_error.err_msg)

        if asan_error.signature.startswith("memory-leak@"):
            # count the times of memory leak crashes
            self.leak_times += 1

        return self.crashes[asan_error.signature]

    @property
    def leak_times(self) -> int:
        """
        The times of memory leak crashes. Used to disable LeakSanitizer.
        """
        if not hasattr(self, "_leak_times"):
            return 0
        return self._leak_times

    @leak_times.setter
    def leak_times(self, value: int):
        self._leak_times = value
        if (
            value > self.DISABLE_LEAK_SANITIZER_THRESHOLD
            and self.DISABLE_LEAK_SANITIZER_THRESHOLD > 0
            and not hasattr(self, "_disable_leak_sanitizer")
        ):
            # the crash happens too many times, disable LeakSanitizer
            DriverRunAttempt.ASAN_OPTIONS.append("detect_leaks=0")
            DriverRunAttempt.asan_options_set = False
            logger.warning(
                f"Memory leak crashes happened {value} times, LeakSanitizer will be disabled then"
            )
            self._disable_leak_sanitizer = True


class ConstraintLearner:
    """
    Class to learn API constraints from mistakes.
    """

    # Whether to enable the learner
    ENABLE_LEARN = True
    # How many times a crash should happen to be considered as a constraint violation
    LEARN_CRASH_THRESHOLD = 3

    def __init__(
        self,
        llm_client: LLMClient,
        info_repo: InfoRepository,
        api_collection: APICollection,
        comprehension: LibraryComprehension,
        crash_recorder: CrashRecorder = CrashRecorder(),
    ):
        """
        Initialize the learner.

        :param llm_client: LLM client
        :info_repo: Information repository from preprocessor
        :param api_collection: API collection from preprocessor
        :param comprehension: Library comprehension
        :param crash_recorder: The crash recorder
        """
        if not self.ENABLE_LEARN:
            self.record_crash = lambda asan_error: None
            return

        self.llm_client = llm_client
        self.report_composer = CrashReportComposer(info_repo, api_collection)
        self.comprehension = comprehension
        self.crash_recorder = crash_recorder

    def record_crash(
        self, asan_error: AsanError
    ) -> Callable[[FuzzDriver], bool] | None:
        """
        Record an ASan crash and return the learning closure.

        :param asan_error: The ASan error
        :return: The learning closure or None if not needed to learn
        """
        crash = self.crash_recorder.record(asan_error)
        if (
            # only learn when the crash happens multiple times
            crash.count >= ConstraintLearner.LEARN_CRASH_THRESHOLD
            # do not learn if the crash has been learned
            and crash.learning_status == CrashRecorder.LearningStatus.NOT_LEARNED
        ):
            crash.learning_status = CrashRecorder.LearningStatus.LEARNING

            def _learning_closure(fuzz_driver: FuzzDriver) -> bool:
                ret = self.learn_constraint(asan_error, fuzz_driver)
                crash.learning_status = (
                    CrashRecorder.LearningStatus.LEARNED
                    if ret
                    else CrashRecorder.LearningStatus.FAILED
                )
                return ret

            return _learning_closure
        else:
            return None

    def learn_constraint(self, asan_error: AsanError, fuzz_driver: FuzzDriver) -> bool:
        """
        Try to learn a constraint from a crash.
        During this process, a fix will be applied to the fuzz driver.

        :param asan_error: The ASan error
        :param fuzz_driver: The fuzz driver
        :return: Whether the fuzz driver is fixed
        """
        crash_sig = asan_error.signature
        logger.debug(f"Learning constraint from crash {crash_sig}")

        # Compose the crash report
        crash_report, related_api_functions = (
            self.report_composer.compose_and_get_related_api_functions(
                asan_error, fuzz_driver.fuzz_driver_code
            )
        )

        # Temporarily ban the related APIs to avoid the same crash
        with Scheduler.TempBanAPIs(related_api_functions):

            # Query the LLM for constraint
            if isinstance(self.llm_client, ReasoningLLMClient):
                prompter = CrashContraintReasoningPrompter(LLMChat(self.llm_client))
            else:
                prompter = CrashConstraintPrompter(LLMChat(self.llm_client))
            constraint, fixed_code = prompter.prompt(
                crash_report=crash_report,
                library_name=global_vars.library_name,
                library_purpose=self.comprehension.purpose,
                api_functions=related_api_functions.function_names,
            )
            fuzz_driver.query_count += 1

            # Determine whether the constraint is effective
            # and add the constraint to the comprehension database if it is
            if not constraint:
                logger.warning(f"No constraint learned from crash {crash_sig}")
                return False
            if not fixed_code:
                logger.error(f"No fixed code generated for crash {crash_sig}")
                return False
            fuzz_driver.fuzz_driver_code = fixed_code
            with DriverRunAttempt(fuzz_driver) as (status, msg):
                if status == "OK":
                    # the constraint is effective, and the fixed code is correct
                    logger.info(
                        f"Successfully fixed crash {crash_sig} with learned constraint"
                    )
                    self._add_constraint_to_comprehension(constraint)
                    return True
                elif status == "CRASH":
                    try:
                        new_asan_error = AsanError(msg)
                    except:
                        logger.error(
                            f"Failed to parse new ASan error when learning constraint from crash {crash_sig}, message: \n{msg}"
                        )
                        return False
                    new_crash_sig = new_asan_error.signature

                    if new_crash_sig == crash_sig:
                        # The constraint is not effective, the same crash happens
                        logger.warning(
                            f"Failed to fix crash {crash_sig} with learned constraint"
                        )
                    else:
                        # The constraint is effective, but the fixed code introduces new crash
                        logger.debug(
                            f"Fixed code introduces new crash {new_crash_sig} when learning constraint from crash {crash_sig}"
                        )
                        self._add_constraint_to_comprehension(constraint)
                    return False
                elif status == "BUILDFAIL":
                    logger.error(
                        f"Unexpected build failure when learning constraint from crash {crash_sig}, message: \n{msg}"
                    )
                    return False

    def _add_constraint_to_comprehension(self, constraints: dict[str, str]):
        """
        Add a constraint to the comprehension database.

        :param constraint: The constraints dict
        """
        # add constraints to function usage
        for func, cons in constraints.items():
            usage = self.comprehension.functions.get(func, "")
            usage += "\n" + cons.strip()
            usage = usage.strip()
            self.comprehension.functions[func] = usage
            logger.info(f"Learned constraint for function {func}: {cons}")

        # save the comprehension
        comp_path = Path(global_vars.library_config["output_path"]) / "comprehender"
        comp_path.mkdir(parents=True, exist_ok=True)
        self.comprehension.dump(comp_path / "comp.pkl")
        self.comprehension.dump_json(comp_path / "comp.json")
