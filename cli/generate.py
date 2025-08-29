"""
Generator command line interface.
"""

import click
from loguru import logger
from enum import StrEnum, auto
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from tqdm import tqdm
from typing import Callable
from math import ceil
import time
import json
import sys
import atexit

from src import vars as global_vars
from src.utils import (
    setup_default_config,
    setup_llm,
    add_hints_to_comprehension,
    ProgressTitle,
)
from src.preprocessor.meta import Meta
from src.preprocessor.information import InfoRepository
from src.preprocessor.api import APICollection
from src.preprocessor.incidental import Incidentals
from src.preprocessor.consumer import OrderSetCollection
from src.preprocessor.relevance import (
    TypeRelevance,
    ClassScopeRelevance,
    CallScopeRelevance,
)
from src.preprocessor.complexity import Complexity
from src.comprehender.comprehender import SemanticRelevance, LibraryComprehension
from src.generator.worker import (
    GenJob,
    SanJob,
    SchedJob,
    Job,
    GenerationState,
    SinglePool,
)
from src.generator.generator import Generator
from src.generator.sanitizer import Sanitizer, DriverRunAttempt
from src.generator.driver import FuzzDriver
from src.generator.scheduler import FunctionSet, Scheduler, RandomScheduler
from src.generator.collector import InfoCollector
from src.generator.synthesizer import SynthesizedDriver, copy_synthesizer_to
from src.generator.learner import ConstraintLearner, CrashRecorder


class TaskOptions(StrEnum):
    GIVEN = auto()
    AUTOSCALE = auto()
    ALLCOVER = auto()


# disable options for ablation study
class DisableOptions(StrEnum):
    COMPREHENDER = auto()
    SCHEDULER = auto()
    SANITIZER = auto()
    ALL = auto()
    NONE = auto()


@click.command(help="Use the LLM to generate fuzz drivers for the target library.")
@click.option(
    "-L",
    "--library",
    "library_name",
    default=None,
    help="The name of the library for generation. You should have it configured in the libraries.toml. \
If the libraries.toml contains only one library, you can omit this option.",
    show_default=True,
)
@click.option(
    "--task",
    "task_option",
    type=click.Choice([_.value for _ in TaskOptions]),
    default=TaskOptions.ALLCOVER.value,
    help="""
The task you wish to perform can be selected from the following options: \
- If choosing "allcover," PromeFuzz will continue generating Fuzz Drivers until \
every function has been tested at least once.\
- If choosing "autoscale," the generation process will run until \
API Occurrence Count = Scale Factor * Number of API Functions. \
- For the "given" option, the generation will focus solely on testing the specific \
functions you provide, which must be listed as arguments.
""",
    show_default=True,
)
@click.option(
    "--disable",
    "disable_option",
    type=click.Choice([_.value for _ in DisableOptions]),
    default=DisableOptions.NONE.value,
    help="""
The module to disable during the generation process, used for ablation studies. \
Select from the following options: \
- "comprehender": Do not provide the comprehended function usage during generation. \
- "scheduler": Do not use the inferred function relationship to choose target functions. \
In the contrary, randomly split all API functions into fixed function set, and generate fuzz drivers for each set. \
- "sanitizer": Do not try to fix the driver which can not compile or run, and directly discard it. \
Meanwhile, do not learn constraints from the crashes. \
- "all": Disable all components. \
- "none": Do not disable any module.
""",
    show_default=True,
)
@click.option(
    "--scale",
    "scale",
    type=float,
    default=5,
    help="""The scale factor for the fuzz driver generation, used in auto-scale mode. \
The whole generation process will not terminate until the total invocation count of API functions \
in the generated fuzz drivers reaches the scale factor multiplied by the number of API functions, \
i.e., API Occurrence Count = Scale Factor * Number of API Functions. \
If set to -1, the generation will never stop until manually halted. \
""",
    show_default=True,
)
@click.option(
    "--clear-state",
    "clear_state",
    is_flag=True,
    help="Clear the generation state and start from scratch.",
    default=False,
)
@click.option(
    "--pool-size",
    "pool_size",
    type=int,
    default=5,
    help="The pool size for the parallel generation.",
    show_default=True,
)
@click.argument(
    "functions",
    nargs=-1,
    type=str,
)
def generate(
    library_name: str,
    task_option: str,
    disable_option: str,
    scale: float,
    clear_state: bool,
    pool_size: int,
    functions: list[str],
):
    """
    Generator cli interface for PromeFuzz
    """
    # ==================== setup configurations ====================
    # setup the default configuration
    setup_default_config(library_name)

    # set some configurations
    generator_config = global_vars.config["generator"]
    Scheduler.FUNCTION_SET_SIZE = generator_config["function_set_size"]
    Scheduler.FUNCTION_FAIL_THRESHOLD = generator_config["function_fail_limit"]
    Scheduler.FUNCTION_FAILTIMES_IF_DRIVER_FAIL = generator_config["function_fail_if_driver_fail"]
    Scheduler.FUNCTION_FAILTIMES_IF_DRIVER_MISS = generator_config["function_fail_if_driver_miss"]
    FunctionSet.MAX_GEN_ROUNDS = generator_config["generation_rounds"]
    FuzzDriver.MAX_SAN_ROUNDS = generator_config["sanitization_rounds"]
    Scheduler.STAGNATION_THRESHOLD = generator_config["stagnation_limit"]
    Scheduler.ORDER_SET_SCHEDULE_THRESHOLD = generator_config["use_consumer_case_count"]
    Scheduler.TYPE_RELEV_WEIGHT = generator_config["schedule_weights"]["type_relevance"]
    Scheduler.CLASS_SCOPE_RELEV_WEIGHT = generator_config["schedule_weights"][
        "class_scope_relevance"
    ]
    Scheduler.CALL_SCOPE_RELEV_WEIGHT = generator_config["schedule_weights"][
        "call_scope_relevance"
    ]
    Scheduler.SEMANTIC_RELEV_WEIGHT = generator_config["schedule_weights"][
        "semantic_relevance"
    ]
    Scheduler.COVRG_WEIGHT = generator_config["schedule_weights"]["coverage"]
    Scheduler.COMPX_WEIGHT = generator_config["schedule_weights"]["complexity"]
    Scheduler.RELEV_WEIGHT = generator_config["schedule_weights"]["relevance"]
    Scheduler.INCIDENTAL_OCCURRENCE_INC = generator_config[
        "incidental_called_api_occurrence_increment"
    ]
    InfoCollector.COLLECT_ONE_IN_SAME_NAMES = generator_config[
        "collect_one_def_in_same_names"
    ]
    InfoCollector.COLLECT_DEPTH = generator_config["collect_depth"]
    Sanitizer.CONSOLIDATE_CHAT_HISTORY = generator_config[
        "enable_chat_history_consolidation"
    ]
    FuzzDriver.USE_POSTPROCESSOR = generator_config[
        "enable_ast_based_api_coverage_check"
    ]
    if FuzzDriver.USE_POSTPROCESSOR:
        if not (bin := Path(global_vars.config["bin"]["cgprocessor"])).is_file():
            logger.critical(
                "The cgprocessor binary is not found, please build it first."
            )
            sys.exit(1)
        FuzzDriver.PROCESSOR_BIN = bin
    if disable_option in [DisableOptions.SANITIZER, DisableOptions.ALL]:
        Sanitizer.DISABLE_FIX = True
        FuzzDriver.MAX_SAN_ROUNDS = 1
    ConstraintLearner.ENABLE_LEARN = generator_config[
        "enable_constraint_learning"
    ] and (
        disable_option
        not in [
            DisableOptions.COMPREHENDER,
            DisableOptions.SANITIZER,
            DisableOptions.ALL,
        ]
    )
    ConstraintLearner.LEARN_CRASH_THRESHOLD = generator_config["learn_crash_threshold"]
    CrashRecorder.DISABLE_LEAK_SANITIZER_THRESHOLD = generator_config[
        "disable_leak_sanitizer_threshold"
    ]
    DriverRunAttempt.CLEANUP = generator_config["cleanup_temp"]
    FuzzDriver.CLEANUP_POST = generator_config["cleanup_temp"]
    CrashRecorder.SAVE_CRASHES = not generator_config["cleanup_temp"]

    # create tmp path
    tmp_path = Path(global_vars.library_config["output_path"]) / "tmp"
    tmp_path.mkdir(parents=True, exist_ok=True)

    # setup the llm
    try:
        generator_llm_client = setup_llm(generator_config["generation_llm"])
        learner_llm_client = setup_llm(global_vars.config["analyzer"]["analysis_llm"])
    except Exception as e:
        logger.critical(f"Failed to setup the LLM client: {e}")
        sys.exit(1)

    # ==================== load extracted information ====================
    # load information repository
    preprocessor_out_path = (
        Path(global_vars.library_config["output_path"]) / "preprocessor"
    )
    try:
        # try to load the information repository from the comprehender output first
        info_repo = InfoRepository.load(preprocessor_out_path / "info.pkl")
    except Exception as e:
        logger.critical(
            f"Failed to load the information repository: {e}, please run the preprocessor first."
        )
        sys.exit(1)

    # load api functions
    try:
        api_collection = APICollection.load(preprocessor_out_path / "api.pkl")
        # check if the function set size is larger than the total number of functions
        if Scheduler.FUNCTION_SET_SIZE > api_collection.count:
            logger.warning(
                f"The function set size ({Scheduler.FUNCTION_SET_SIZE}) is larger than the total number of functions ({api_collection.count})."
                + "Function set size will be set to the total number of functions."
            )
            Scheduler.FUNCTION_SET_SIZE = api_collection.count
    except Exception as e:
        logger.critical(f"Failed to load the API functions: {e}")
        sys.exit(1)

    # load api incidental relationships
    try:
        incidental_path = preprocessor_out_path / "incidentals.pkl"
        incidentals = Incidentals.load(incidental_path)
    except Exception as e:
        logger.critical(f"Failed to load the incidental relationships: {e}")
        sys.exit(1)

    # load api calling order
    try:
        order_sets = OrderSetCollection.load(preprocessor_out_path / "call_order.pkl")
    except:
        # it is optional
        order_sets = None

    # load complexity
    try:
        complexity = Complexity.load(preprocessor_out_path / "complexity.pkl")
    except Exception as e:
        logger.critical(f"Failed to load the complexity: {e}")
        sys.exit(1)

    # load relevance
    try:
        type_relevance = TypeRelevance.load(preprocessor_out_path / "type_relev.pkl")
    except Exception as e:
        logger.warning(f"Failed to load the type relevance: {e}")
        type_relevance = None
    try:
        class_scope_relevance = ClassScopeRelevance.load(
            preprocessor_out_path / "class_scope_relev.pkl"
        )
    except Exception as e:
        if global_vars.library_language == global_vars.SupportedLanguages.CPP:
            logger.warning(f"Failed to load the class scope relevance: {e}")
        class_scope_relevance = None
    try:
        call_scope_relevance = CallScopeRelevance.load(
            preprocessor_out_path / "call_scope_relev.pkl"
        )
    except Exception as e:
        if global_vars.library_config["consumer_case_paths"]:
            logger.warning(f"Failed to load the call scope relevance: {e}")
        call_scope_relevance = None
    comprehender_out_path = (
        Path(global_vars.library_config["output_path"]) / "comprehender"
    )
    try:
        semantic_relevance = SemanticRelevance.load(
            comprehender_out_path / "semantic_relev.pkl"
        )
    except:
        # This is optional
        logger.warning(
            "Semantic relevance not found. You can run the comprehender to get the semantic relevance."
        )
        semantic_relevance = None

    # load comprehension
    try:
        if disable_option in [DisableOptions.COMPREHENDER, DisableOptions.ALL]:
            raise Exception("Comprehender is disabled.")
        comprehension = LibraryComprehension.load(comprehender_out_path / "comp.pkl")
    except Exception as e:
        # it is optional
        comprehension = LibraryComprehension("", {})
        logger.warning(
            f"Comprehension not loaded: {e} The generator will run without comprehension."
        )
    else:
        if not comprehension.purpose:
            logger.warning("Library purpose not comprehended. Skipping.")
        if not comprehension.functions:
            logger.warning("Function purpose and usage not comprehended. Skipping.")

    # load api hints
    api_hints_path = global_vars.library_config["api_hints_path"]
    if api_hints_path and (
        disable_option
        not in [
            DisableOptions.COMPREHENDER,
            DisableOptions.ALL,
        ]
    ):
        try:
            api_hints = json.loads(Path(api_hints_path).read_text())
        except Exception as e:
            logger.warning(
                f"Failed to load the API hints specified in {api_hints_path}: {e}"
            )
        else:
            add_hints_to_comprehension(comprehension, api_hints)

    # ==================== setup workers ====================
    # setup generator, learner, sanitizer, and scheduler
    generator = Generator(generator_llm_client, info_repo, comprehension)
    GenJob.generator = generator

    crash_recorder = CrashRecorder()
    learner = ConstraintLearner(
        learner_llm_client,
        info_repo,
        api_collection,
        comprehension,
        crash_recorder,
    )

    sanitizer = Sanitizer(learner)
    SanJob.sanitizer = sanitizer

    driver_save_path = Path(global_vars.library_config["output_path"]) / "fuzz_driver"
    driver_save_path.mkdir(parents=True, exist_ok=True)
    copy_synthesizer_to(driver_save_path)
    SanJob.save_path = driver_save_path

    scheduler_class = (
        RandomScheduler
        if disable_option in [DisableOptions.SCHEDULER, DisableOptions.ALL]
        else Scheduler
    )
    scheduler = scheduler_class(
        api_collection=api_collection,
        api_incidentals=incidentals,
        complexity=complexity,
        api_order_collection=order_sets,
        type_relevance=type_relevance,
        class_scope_relevance=class_scope_relevance,
        call_scope_relevance=call_scope_relevance,
        semantic_relevance=semantic_relevance,
    )
    SchedJob.scheduler = scheduler
    SanJob.scheduler = scheduler
    SanJob.api_collection = api_collection

    # setup generator state
    state_path = (
        Path(global_vars.library_config["output_path"]) / "generator" / "state.pkl"
    )
    if state_path.exists() and not clear_state:
        state = GenerationState.load(state_path)
    else:
        state_path.parent.mkdir(parents=True, exist_ok=True)
        state = GenerationState(api_collection, state_path)
    Job.state = state
    state.restore(scheduler, crash_recorder)

    # =================== run tasks ===================
    def run_given():
        """
        Run in given mode
        """
        # check if functions are provided
        if not functions:
            logger.critical("No functions provided.")

        # get target functions
        given_functions = []
        for fun_name in functions:
            if func := api_collection.get_by_name(fun_name):
                given_functions.extend(func)
            else:
                logger.error(
                    f"Function {fun_name} not found in the API function collection."
                )
        target_functions = FunctionSet(given_functions)

        # worker pool
        Job.pool = SinglePool()

        # add generation job to the pool
        gen_job = GenJob(target_functions)
        gen_job.submit()

    def _single_thread_run(stop_condition: Callable[[], bool]):
        """
        Run in single thread mode

        :param stop_condition: The stop condition for the generation
        """
        pool = SinglePool()
        Job.pool = pool

        while not stop_condition():
            sched_job = SchedJob()
            sched_job.submit()

    def _multi_thread_run(stop_condition: Callable[[], bool]):
        """
        Run in multi thread mode

        :param stop_condition: The stop condition for the generation
        """
        pool = ThreadPoolExecutor(max_workers=pool_size)
        Job.pool = pool

        while not stop_condition():
            # in main thread, detect the pool task count, if it is less than pool size, add scheduling job to the pool
            if (task_count := pool._work_queue.qsize()) < pool_size:
                for _ in range(pool_size - task_count):
                    sched_job = SchedJob()
                    sched_job.submit()
            time.sleep(1)

    def _synthesize():
        """
        Synthesize the fuzz drivers
        """
        # synthesize the fuzz drivers
        try:
            synthesized_driver = SynthesizedDriver.from_dir(driver_save_path)
        except FileNotFoundError:
            logger.warning("No fuzz driver generated, skipping synthesis.")
            return
        synthesized_driver.save(driver_save_path)
        logger.success(
            f"Generation completed. Synthesized driver saved to {str(driver_save_path)}."
        )

    def run_allcover():
        """
        Run generation process in all-cover mode
        """
        # set progress bar
        scheduler.func_cover_progress_bar = tqdm(
            total=api_collection.count,
            desc=("[ALL-COVER MODE] Generating Fuzz Drivers"),
            unit="tested functions",
            colour="green",
            leave=False,
        )
        scheduler.func_cover_progress_bar.update(
            scheduler.statistics.total_tested
            + len(scheduler.statistics.deprecated_functions)
        )

        def _stop_condition():
            if scheduler.all_functions_occurred:
                return True

            if scheduler.stagnation_counter < 0 and scheduler.STAGNATION_THRESHOLD > 0:
                # Stagnation check is enabled and the counter is negative
                logger.error("Stagnation detected, stopping the generation.")
                return True

            return False

        # run tasks
        if pool_size == 1:
            _single_thread_run(_stop_condition)
        else:
            _multi_thread_run(_stop_condition)

        # wait for the pool to finish
        with ProgressTitle(
            "Generation done, waiting for the remaining tasks. If you want to quit now, press Ctrl+C."
        ):
            exit(0)

    def run_autoscale():
        """
        Run generation process in autoscale mode
        """
        if scale < 0:
            logger.warning(
                "The scale factor is set to -1, the generation will run indefinitely."
            )
            target_occurrence = float("inf")
        else:
            target_occurrence = ceil(api_collection.count * scale)

        # set progress bar
        scheduler.func_occurrence_progress_bar = tqdm(
            total=target_occurrence,
            desc=("[AUTO-SCALE MODE] Generating Fuzz Drivers"),
            unit="invocations",
            colour="green",
            leave=False,
        )
        scheduler.func_occurrence_progress_bar.update(
            scheduler.statistics.total_occurrences
        )

        def _stop_condition():
            if scheduler.statistics.total_occurrences >= target_occurrence:
                return True
            return False

        # run tasks
        if pool_size == 1:
            _single_thread_run(_stop_condition)
        else:
            _multi_thread_run(_stop_condition)

        # wait for the pool to finish
        with ProgressTitle(
            "Generation done, waiting for the remaining tasks. If you want to quit now, press Ctrl+C."
        ):
            exit(0)

    def run_non_scheduler():
        """
        Run the generation without the scheduler.
        """
        progress = tqdm(
            total=len(scheduler.random_splitted_functions),
            desc="[SCHED DISABLED] Generating Fuzz Drivers",
            unit="function set",
            colour="green",
        )
        Job.pool = SinglePool()

        function_sets = []
        while (s := scheduler.schedule()) is not None:
            function_sets.append(s)

        def _run(function_set: FunctionSet):
            gen_job = GenJob(function_set)
            gen_job.submit()
            progress.update(1)

        if pool_size > 1:
            with ThreadPoolExecutor(max_workers=pool_size) as pool:
                pool.map(_run, function_sets)
        else:
            for function_set in function_sets:
                _run(function_set)
        progress.close()

    # run tasks
    atexit.register(_synthesize)  # synthesize the fuzz drivers when the program exits
    if disable_option in [DisableOptions.SCHEDULER, DisableOptions.ALL]:
        run_non_scheduler()
    elif task_option == TaskOptions.GIVEN.value:
        run_given()
    elif task_option == TaskOptions.AUTOSCALE.value:
        run_autoscale()
    elif task_option == TaskOptions.ALLCOVER.value:
        Scheduler.IN_ALLCOVER_MODE = True
        run_allcover()
