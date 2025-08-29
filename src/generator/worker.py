"""
Worker classes for the generator
"""

from loguru import logger
from abc import ABC, abstractmethod
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path
import pickle
import time

from src import vars as global_vars
from src.utils import ProgressTitle, SinglePool
from src.llm.llm import LLMClient, QueryStats
from src.preprocessor.consumer import OrderSet
from .scheduler import Scheduler, FunctionSet, APICollection, SchedStatistics
from .generator import Generator
from .sanitizer import Sanitizer
from .driver import FuzzDriver
from .learner import CrashRecorder


class Job(ABC):
    """
    Class to represent a multi-threaded job
    """

    pool: ThreadPoolExecutor | SinglePool = None
    state: "GenerationState" = None

    def __init__(self): ...

    @abstractmethod
    def run(self): ...

    def submit(self):
        """
        Submit the job to the pool
        """
        self.pool.submit(self.run)


class SchedJob(Job):
    """
    Class to represent a scheduling job
    """

    scheduler: Scheduler = None

    def __init__(self):
        """
        Initialize a scheduling job
        """
        pass

    def run(self):
        """
        Run the scheduling job
        """
        # get the next function set
        target_functions = self.scheduler.schedule()
        if not target_functions:
            return

        # save the generator state
        function_set = target_functions.as_function_set if isinstance(target_functions, OrderSet) else target_functions
        self.state.update(function_set)

        # add generation job to the pool
        gen_job = GenJob(target_functions)
        gen_job.submit()


class GenJob(Job):
    """
    Class to represent a generation job
    """

    generator: Generator = None

    def __init__(
        self,
        target_functions: FunctionSet | OrderSet,
    ):
        """
        Initialize a generation job

        :param target_functions: The target functions to be fuzzed, could be a normal function set or an order set
        """
        self.target_functions = target_functions

    def run(self):
        """
        Run the generation job
        """
        # generate the fuzz driver
        set_id = (
            self.target_functions.id
            if isinstance(self.target_functions, FunctionSet)
            else self.target_functions.as_function_set.id
        )
        with ProgressTitle(f"Generating Driver for function set {set_id}"):
            fuzz_driver = self.generator.generate(self.target_functions)

        if fuzz_driver:
            # save the generator state
            self.state.update(fuzz_driver)

            # add sanitization job to the pool
            san_job = SanJob(fuzz_driver)
            san_job.submit()


class SanJob(Job):
    """
    Class to represent a sanitization job
    """

    sanitizer: Sanitizer = None
    save_path = None
    scheduler: Scheduler = None
    api_collection: APICollection = None

    def __init__(
        self,
        fuzz_driver: FuzzDriver,
    ):
        """
        Initialize a sanitization job

        :param fuzz_driver: The fuzz driver to be sanitized
        """
        self.fuzz_driver = fuzz_driver

    def run(self):
        """
        Run the sanitization job
        """
        # sanitize the fuzz driver
        with ProgressTitle(f"Sanitizing Driver {self.fuzz_driver.id}"):
            self.sanitizer.sanitize(self.fuzz_driver)

        # update state
        self.state.update(self.fuzz_driver)

        if self.fuzz_driver.sanitized:
            # if sanitized, the fuzz driver has been generated successfully
            self.san_success()
        elif self.fuzz_driver.remain_san_rounds > 0:
            # if not reached the max round, add sanitization job to the pool
            san_job = SanJob(self.fuzz_driver)
            san_job.submit()
        else:
            # if reached the max round, treat as failure
            self.san_failure()

    def san_success(self):
        """
        Function to run when sanitization is successful
        """
        # check its actual target functions
        actual_targets, missing_targets = self.fuzz_driver.check_actual_targets(
            self.api_collection
        )
        if missing_targets:
            logger.warning(
                "Fuzz driver {} does not cover the following functions in function set {}: \n{}".format(
                    self.fuzz_driver.id,
                    self.fuzz_driver.function_set.id,
                    ", ".join(str(_f) for _f in missing_targets),
                )
            )
            # record the function failed times
            self.scheduler.record_functions_failed(
                missing_targets,
                increment=self.scheduler.FUNCTION_FAILTIMES_IF_DRIVER_MISS
            )
        if not actual_targets:
            # discard the fuzz driver if it does not cover any functions
            logger.warning(
                "Fuzz driver {} does not cover any functions in function set {}".format(
                    self.fuzz_driver.id, self.fuzz_driver.function_set.id
                )
            )
            return
        logger.info(
            "Fuzz driver {} tests the following functions: \n{}".format(
                self.fuzz_driver.id,
                ", ".join(str(_f) for _f in actual_targets),
            )
        )
        # record the function set as tested
        self.scheduler.record_functions_occurrence(actual_targets)
        # save the scheduler state
        self.state.update(self.scheduler)
        # save the fuzz driver
        comment = "This fuzz driver is generated for library {}, aiming to fuzz the following functions:\n{}".format(
            global_vars.library_name,
            "\n".join(str(_f) for _f in actual_targets),
        )
        self.fuzz_driver.save(
            self.save_path, save_build_script=True, add_comment=comment
        )
        logger.success(
            f"Fuzz driver {self.fuzz_driver.id} has been successfully generated and sanitized, saved to {self.save_path}"
        )

    def san_failure(self):
        """
        Function to run when sanitization fails
        """
        # record the function failed times
        self.scheduler.record_functions_failed(
            self.fuzz_driver.function_set.funcs,
            increment=self.scheduler.FUNCTION_FAILTIMES_IF_DRIVER_FAIL,
        )

        if self.fuzz_driver.function_set.remain_gen_rounds > 0:
            # if still have remaining gen rounds, regenerate the fuzz driver
            logger.warning(
                f"Fuzz driver {self.fuzz_driver.id} has reached the maximum sanitization rounds, regenerating..."
            )
            gen_job = GenJob(self.fuzz_driver.target_functions)
            gen_job.submit()
        else:
            logger.warning(
                f"Function set {self.fuzz_driver.function_set.id} has reached the maximum generation rounds, discarded."
            )


@dataclass
class GenerationState:
    """
    Class to store the state of the generation
    """

    scheduler_statistics: SchedStatistics
    """
    The statistics of the scheduler
    """

    llm_statistics: QueryStats
    """
    The statistics of the LLM
    """

    fuzz_driver_number: int
    """
    The number of fuzz drivers generated, used for fuzz driver ID
    """

    fuzz_driver_query_count: dict[int, int]
    """
    The number of queries already sent to generate the fuzz driver, driver ID as key
    """

    fuzz_driver_success: dict[int, bool]
    """
    Whether the fuzz driver is successfully generated and saved, driver ID as key
    """

    function_set_number: int
    """
    The number of function sets generated, used for function set ID
    """

    crashes: dict[str, CrashRecorder.RecordedCrash]
    """
    The recorded crashes during the generation
    """

    timestamp: float
    """
    The timestamp of the state last updated
    """

    duration: float = 0.0
    """
    The duration of the generation
    """

    def __init__(self, api_collection: APICollection, persistency_path: Path):
        """
        Initialize the generation state

        :param api_collection: The API collection
        :param persistency_path: The path to save the state
        """
        self.path = persistency_path

        self.scheduler_statistics = SchedStatistics(api_collection)
        self.llm_statistics = QueryStats.from_empty()
        self.fuzz_driver_number = 0
        self.fuzz_driver_query_count = {}
        self.fuzz_driver_success = {}
        self.function_set_number = 0
        self.crashes = {}
        self.timestamp = time.time()

    @classmethod
    def load(cls, path: Path):
        """
        Load the state of the generation from a file

        :param path: The path to the state file
        """
        with open(path, "rb") as f:
            state: GenerationState = pickle.load(f)
        return state

    def save(self):
        """
        Save the state of the generation
        """
        with open(self.path, "wb") as f:
            pickle.dump(self, f)

    def save_human(self):
        """
        Save the state of the generation to a human-readable txt file
        """
        import pprint

        with open(self.path.with_suffix(".txt"), "w") as f:
            pprint.pprint(vars(self), stream=f)

    def update(
        self, obj: FunctionSet | FuzzDriver | Scheduler | CrashRecorder | LLMClient
    ):
        """
        Update the generation state

        :param obj: The object to update the state
        """
        if isinstance(obj, FunctionSet):
            self.function_set_number = obj.gen_count
        elif isinstance(obj, FuzzDriver):
            self.fuzz_driver_number = obj.gen_count
            self.fuzz_driver_query_count[obj.id] = obj.query_count
            self.fuzz_driver_success[obj.id] = obj.sanitized
        elif (
            isinstance(obj, Scheduler)
            or isinstance(obj, LLMClient)
            or isinstance(obj, CrashRecorder)
        ):
            # No need to assign, because it is a reference to the object and its value will be updated automatically
            pass
        timenow = time.time()
        self.duration += timenow - self.timestamp
        self.timestamp = timenow
        self.save()
        self.save_human()

    def restore(self, scheduler: Scheduler, crash_recorder: CrashRecorder):
        """
        Restore the generation state

        :param scheduler: The scheduler
        :param crash_recorder: The crash recorder
        """
        logger.info(
            "Resuming generation state from {}. Last generated fuzz driver {}, last scheduled function set {}".format(
                time.ctime(self.timestamp),
                self.fuzz_driver_number,
                self.function_set_number,
            )
        )
        self.timestamp = time.time()
        LLMClient.query_logger.stats = self.llm_statistics
        FunctionSet.gen_count = self.function_set_number
        FuzzDriver.gen_count = self.fuzz_driver_number
        scheduler.statistics = self.scheduler_statistics
        crash_recorder.crashes = self.crashes
