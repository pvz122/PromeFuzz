"""
Schedule the functions to be generated.
"""

import threading
from loguru import logger
from functools import cache, cached_property
import threading
import random
from dataclasses import dataclass
from tqdm import tqdm

from src.preprocessor.api import APICollection, APIFunction
from src.preprocessor.incidental import Incidentals
from src.preprocessor.consumer import OrderSet, OrderSetCollection
from src.preprocessor.relevance import (
    TypeRelevance,
    ClassScopeRelevance,
    RelevanceCalculator,
    CallScopeRelevance,
)
from src.preprocessor.complexity import Complexity
from src.comprehender.comprehender import SemanticRelevance


class FunctionSet(APICollection):
    """
    Class to store the target function set
    """

    MAX_GEN_ROUNDS = 7

    lock = threading.Lock()
    gen_count = 0

    def __init__(
        self,
        functions: list[APIFunction],
        increment_id: bool = True,
    ):
        """
        Initialize the function set

        :param functions: The target functions to be fuzzed
        :param increment_id: Whether to increment the id
        """
        self.remain_gen_rounds = self.MAX_GEN_ROUNDS
        if increment_id:
            self.id = self._new_id()
        else:
            self.id = -1
        super().__init__(functions)

    @staticmethod
    def _new_id() -> int:
        """
        Generate a new id

        :return: The new id
        """
        with FunctionSet.lock:
            FunctionSet.gen_count += 1
            new_id = FunctionSet.gen_count
        return new_id


@dataclass
class SchedStatistics:
    """
    Class to store the scheduling statistics
    """

    order_set_utilized: int
    """
    The number of order sets that have been utilized
    """

    total_occurrences: float
    """
    The total number of occurrences of the functions in the fuzz driver
    """

    function_occurrences: dict[APIFunction, float]
    """
    The number of occurrences of each function in the fuzz driver
    """

    total_tested: int
    """
    The total number of functions that have occurred at least once in the fuzz driver
    """

    function_tested: dict[APIFunction, bool]
    """
    Whether each function has occurred at least once in the fuzz driver
    """

    function_failed_times: dict[APIFunction, float]
    """
    The times each function has failed to generate
    """

    deprecated_functions: list[APIFunction]
    """
    The deprecated functions which should not be scheduled
    """

    def __init__(self, api_collection: APICollection):
        """
        Initialize a empty statistics

        :param api_collection: The API function collection
        """
        self.order_set_utilized = 0
        self.total_occurrences = 0
        self.total_tested = 0
        self.function_occurrences = {func: 0 for func in api_collection.safe_iter}
        self.function_tested = {func: False for func in api_collection.safe_iter}
        self.function_failed_times = {func: 0 for func in api_collection.safe_iter}
        self.deprecated_functions = []


class Scheduler:
    """
    Class to schedule the functions to be generated
    """

    # function set size
    FUNCTION_SET_SIZE = 8
    # The max number of order sets to be scheduled
    ORDER_SET_SCHEDULE_THRESHOLD = 50
    # The weights of the relevance
    TYPE_RELEV_WEIGHT = 2
    CLASS_SCOPE_RELEV_WEIGHT = 1
    CALL_SCOPE_RELEV_WEIGHT = 3
    SEMANTIC_RELEV_WEIGHT = 5
    # The weight of scheduling score
    COVRG_WEIGHT = 3
    COMPX_WEIGHT = 2
    RELEV_WEIGHT = 1
    # The threshold of function fail times
    # If a fuzz driver fails to generate, the `failed_times` for the target API functions
    # will increase by `FUNCTION_FAILTIMES_IF_DRIVER_FAIL` times.
    # If a fuzz driver succeeds, but some target API functions are missed,
    # the `failed_times` for the target API functions will increase by `FUNCTION_FAILTIMES_IF_DRIVER_MISS` times.
    # If the `failed_times` for a target API function reaches `FUNCTION_FAIL_THRESHOLD`,
    # the function will be marked as "deprecated" and will not be scheduled again.
    FUNCTION_FAIL_THRESHOLD = 5
    FUNCTION_FAILTIMES_IF_DRIVER_FAIL = 1.0
    FUNCTION_FAILTIMES_IF_DRIVER_MISS = 0.5
    # The increment of the incidental API occurrence
    INCIDENTAL_OCCURRENCE_INC = 0.2

    # Whether to schedule functions in all-cover mode
    # in which the first scheduled function must be an uncovered one
    IN_ALLCOVER_MODE = False

    # a useful place holder function
    PLACEHOLDER_FUNCTION = APIFunction(
        "placeholder", "placeholder", "placeholder", "placeholder"
    )

    # If scheduled STAGNATION_THRESHOLD times, there are still no new functions tested, the scheduler will stop
    # Set to -1 to disable this feature
    STAGNATION_THRESHOLD = 10

    def __init__(
        self,
        api_collection: APICollection,
        api_incidentals: Incidentals,
        complexity: Complexity,
        api_order_collection: OrderSetCollection = None,
        type_relevance: TypeRelevance = None,
        class_scope_relevance: ClassScopeRelevance = None,
        call_scope_relevance: CallScopeRelevance = None,
        semantic_relevance: SemanticRelevance = None,
    ):
        """
        Initialize the scheduler

        :param api_collection: API functions from preprocessor
        :param api_incidentals: API incidental relationships
        :param complexity: Complexity of the API functions
        :param api_order_collection: API order sets from consumer
        :param type_relevance: Type relevance of the API functions
        :param class_scope_relevance: Class scope relevance of the API functions
        :param call_scope_relevance: Call scope relevance of the API functions
        :param semantic_relevance: Function relevance of the API functions
        """
        # set the API functions
        self.api_collection = api_collection
        self.api_incidentals = api_incidentals
        self.order_sets = api_order_collection
        self.complexity = complexity

        # set ban API stuff
        Scheduler.TempBanAPIs.scheduler = self
        self._temp_bans: list[FunctionSet] = []

        # set statistics
        self.statistics = SchedStatistics(api_collection)

        # set the relevance calculator
        self.relevance = RelevanceCalculator()
        if type_relevance is not None:
            self.relevance.add_relevance_aspect(type_relevance, self.TYPE_RELEV_WEIGHT)
        if class_scope_relevance is not None:
            self.relevance.add_relevance_aspect(
                class_scope_relevance, self.CLASS_SCOPE_RELEV_WEIGHT
            )
        if call_scope_relevance is not None:
            self.relevance.add_relevance_aspect(
                call_scope_relevance, self.CALL_SCOPE_RELEV_WEIGHT
            )
        if semantic_relevance is not None:
            self.relevance.add_relevance_aspect(
                semantic_relevance, self.SEMANTIC_RELEV_WEIGHT
            )

        # set mutex lock
        self.lock = threading.Lock()

        # set progress bar to None
        # If progress bar is needed, the main loop should set it
        self.func_cover_progress_bar: tqdm = None
        self.func_occurrence_progress_bar: tqdm = None

        # set stagnation counter
        self.stagnation_counter = self.STAGNATION_THRESHOLD

    @property
    def banned_APIs(self) -> list[APIFunction]:
        """
        Get the banned functions, including the temporary banned functions and the deprecated functions
        """
        return self.statistics.deprecated_functions + self.temp_banned_APIs

    @property
    def temp_banned_APIs(self) -> list[APIFunction]:
        """
        The temporarily banned functions
        """
        return list(
            set(
                func
                for banned_apis in self._temp_bans
                for func in banned_apis.safe_iter
            )
        )

    class TempBanAPIs:
        """
        Ban the APIs temporarily
        Use it with the `with` statement to manage temporary bans
        """

        scheduler: "Scheduler" = None

        def __init__(self, banned_apis: FunctionSet):
            self.banned_apis = banned_apis

        def __enter__(self):
            with self.scheduler.lock:
                self.scheduler._temp_bans.append(self.banned_apis)
            logger.debug(f"Temporarily ban APIs:\n{self.banned_apis}")

        def __exit__(self, exc_type, exc_val, exc_tb):
            with self.scheduler.lock:
                i = self.scheduler._temp_bans.index(self.banned_apis)
                self.scheduler._temp_bans.pop(i)
            logger.debug(f"Unban APIs:\n{self.banned_apis}")

    def record_functions_occurrence(self, occurrent_functions: list[APIFunction]):
        """
        Record the occurrence of the functions in the fuzz driver

        :param tested_functions: The tested functions
        """

        def _record_statistics(func: APIFunction, occ_increment: float = 1):
            # record the occurrence of the function
            self.statistics.total_occurrences += occ_increment
            self.statistics.function_occurrences[func] += occ_increment
            # update the func occurrence progress bar
            if self.func_occurrence_progress_bar is not None:
                self.func_occurrence_progress_bar.update(occ_increment)

            # check if the function has been tested
            if not self.statistics.function_tested[func]:
                # record the function as tested
                self.statistics.total_tested += 1
                self.statistics.function_tested[func] = True
                # reset the stagnation counter
                self.stagnation_counter = self.STAGNATION_THRESHOLD
                # update the func cover progress bar
                if self.func_cover_progress_bar is not None:
                    self.func_cover_progress_bar.update(1)

        with self.lock:
            # minus the stagnation counter
            self.stagnation_counter -= 1
            for func in occurrent_functions:
                _record_statistics(func)
                if self.INCIDENTAL_OCCURRENCE_INC > 0:
                    # record the incidental functions
                    for incidental in self.api_incidentals.get(func):
                        # for incidental functions, because they are not tested directly
                        # the occurrence increment is smaller
                        _record_statistics(incidental, self.INCIDENTAL_OCCURRENCE_INC)

    def record_functions_failed(
        self, failed_functions: list[APIFunction], increment: float = 1
    ):
        """
        Record the failed generation of the functions

        :param failed_functions: The failed functions
        :param increment: The increment of the function_failed_times
        """
        with self.lock:
            # minus the stagnation counter
            self.stagnation_counter -= 1
            for func in failed_functions:
                self.statistics.function_failed_times[func] += increment
                if (
                    self.statistics.function_failed_times[func]
                    > self.FUNCTION_FAIL_THRESHOLD
                ) and (
                    # Because of the parallelism, another thread may have recorded the function as tested
                    self.statistics.function_tested[func]
                    is False
                ):
                    logger.warning(
                        f"Function {func.name} has failed to generate more than {self.FUNCTION_FAIL_THRESHOLD} times, deprecated."
                    )
                    self.statistics.deprecated_functions.append(func)
                    if self.func_cover_progress_bar is not None:
                        self.func_cover_progress_bar.update(1)

    @property
    def all_functions_occurred(self) -> bool:
        """
        Check if all functions have occurred at least once

        :return: Whether all functions have occurred at least once
        """
        return (
            self.statistics.total_tested + len(self.statistics.deprecated_functions)
            >= self.api_collection.count
        )

    def _get_function_coverage(self, func: APIFunction) -> float:
        """
        Get the occurrence degree of the function

        :param func: The function to be checked
        :return: The test degree of the function
        """
        return (
            0
            if self.statistics.total_occurrences == 0
            else (
                self.statistics.function_occurrences[func]
                / self.statistics.total_occurrences
            )
        )

    @cache
    def _get_function_relevance(
        self, func_a: APIFunction, func_b: APIFunction
    ) -> float:
        """
        Get the relevance of two functions

        :param func_a: The first function
        :param func_b: The second function
        :return: The relevance of the two functions
        """
        return (
            0
            if (
                func_a == self.PLACEHOLDER_FUNCTION
                or func_b == self.PLACEHOLDER_FUNCTION
            )
            else self.relevance.get_relevance(func_a.loc, func_b.loc)
        )

    def _min_max_norm(self, value: float, min_value: float, max_value: float) -> float:
        """
        Min-max normalization
        """
        if max_value == min_value:
            # avoid division by zero
            return 0

        return (value - min_value) / (max_value - min_value)

    def schedule(self) -> FunctionSet | OrderSet | None:
        """
        Schedule the functions, emitting a function set or an order set

        :return: The FunctionSet or OrderSet object
        """
        if (order_set := self.schedule_order()) is not None:
            return order_set
        else:
            return self.schedule_normal()

    def schedule_order(self) -> OrderSet | None:
        """
        Emit a function order set, which is from the consumer code

        :return: The OrderSet object, later to be the target functions. None if no order set is available.
        """
        if self.order_sets is None:
            # if no order sets
            return None
        if (
            self.statistics.order_set_utilized > self.ORDER_SET_SCHEDULE_THRESHOLD
            and self.ORDER_SET_SCHEDULE_THRESHOLD != -1
        ):
            # if the utilized order sets exceed the threshold
            return None
        if self.statistics.order_set_utilized >= len(self.order_sets):
            # if the order sets are exhausted
            return None

        logger.info("Scheduling new order set...")
        order_set_index = self.statistics.order_set_utilized
        with self.lock:
            self.statistics.order_set_utilized += 1
        return self.order_sets[order_set_index]

    def schedule_normal(self) -> FunctionSet | None:
        """
        Schedule the functions, emitting a normal function set based on the relevance

        :return: The FunctionSet object, later to be the target functions
        """
        # INPUT: api functions, function set size, every two functions' relevance, every function's coverage
        # OUTPUT: a function set
        # ALGORITHM:
        # 1. add placeholder function f0 to the function set, its relevance with every other function is 0
        # 2. for every other function fp in the api functions, calculate the Schedule Score:
        #    RelevanceSum(fp) = sum(Relevance(f, fp) for f in function set)
        #    ScheduleScore(fp) = COVRG_WEIGHT * (1 - Coverage(fp)) + \
        #                        COMPX_WEIGHT * Complexity(fp) + \
        #                        RELEV_WEIGHT * MinMaxNorm(RelevanceSum(fp)) \
        #                        / (COVRG_WEIGHT + COMPX_WEIGHT + RELEV_WEIGHT)
        # 3. select the function with the highest Schedule Score, add it to the function set
        # 4. repeat step 2 and 3 until the function set size is reached
        # 5. remove the placeholder function f0 from the function set and return the function set

        logger.info("Scheduling new function set...")

        # initialize the function set
        function_set = FunctionSet([self.PLACEHOLDER_FUNCTION])

        # should be <= because of the placeholder
        while function_set.count <= self.FUNCTION_SET_SIZE:
            # check candidate functions
            candidate_functions = [
                func
                for func in self.api_collection.safe_iter
                if ((not function_set.has(func)) and (func not in self.banned_APIs))
            ]
            if not candidate_functions:
                logger.warning(
                    f"There are no more candidate functions to be scheduled, the function set size is {function_set.count - 1}"
                )
                break

            # handle all-cover mode, the first function must be an uncovered one
            if self.IN_ALLCOVER_MODE and function_set.count == 1:
                # select the function with the lowest coverage
                try:
                    selected_func = random.choice(
                        [
                            func
                            for func in candidate_functions
                            if self._get_function_coverage(func) == 0
                        ]
                    )
                except IndexError:
                    # there are no uncovered functions, should not happen
                    logger.warning("There are no uncovered functions to be scheduled.")
                    return None
                logger.debug(
                    "Selected uncovered function {}".format(
                        selected_func.name,
                    )
                )
                function_set.append(selected_func)
                continue

            # calculate the relevance sums and schedule scores
            relevance_sums: dict[APIFunction, float] = {}
            schedule_scores: dict[APIFunction, float] = {}

            # calculate the relevance sums
            for candidate_func in candidate_functions:
                relevance_sums[candidate_func] = sum(
                    self._get_function_relevance(candidate_func, func_in_set)
                    for func_in_set in function_set.safe_iter
                )
            max_relevance_sum = max(relevance_sums.values())
            min_relevance_sum = min(relevance_sums.values())

            # calculate the schedule scores
            for func in relevance_sums:
                schedule_scores[func] = (
                    self.COVRG_WEIGHT * (1 - self._get_function_coverage(func))
                    + self.COMPX_WEIGHT * self.complexity[func]
                    + self.RELEV_WEIGHT
                    * self._min_max_norm(
                        relevance_sums[func], min_relevance_sum, max_relevance_sum
                    )
                ) / (self.COVRG_WEIGHT + self.COMPX_WEIGHT + self.RELEV_WEIGHT)

            # select the function with the highest schedule score
            max_score = max(schedule_scores.values())
            # randomly select one if there are multiple functions with the same score
            selected_func = random.choice(
                [func for func, score in schedule_scores.items() if score == max_score]
            )
            logger.debug(
                "Selected function {} with schedule score {}, coverage {}, complexity {}, relevance sum {}".format(
                    selected_func.name,
                    schedule_scores[selected_func],
                    self._get_function_coverage(selected_func),
                    self.complexity[selected_func],
                    relevance_sums[selected_func],
                )
            )

            # add the selected function to the function set
            function_set.append(selected_func)

        # remove the placeholder function
        function_set.remove(self.PLACEHOLDER_FUNCTION)

        logger.info(
            f"New function set scheduled, id {function_set.id}: \n{function_set}"
        )
        return function_set


class RandomScheduler(Scheduler):
    """
    Random scheduler that simply splits the API functions into fixed-size function sets randomly.
    """

    @cached_property
    def random_splitted_functions(self) -> list[list[APIFunction]]:
        """
        The random splitted functions.
        """
        splitted_functions = []
        functions = list(self.api_collection.safe_iter)
        random.shuffle(functions)
        for i in range(0, len(functions), self.FUNCTION_SET_SIZE):
            splitted_functions.append(functions[i : i + self.FUNCTION_SET_SIZE])
        return splitted_functions

    def schedule(self) -> FunctionSet | None:
        """
        Schedule the functions, emitting a function set based on random selection

        :return: The FunctionSet object, later to be the target functions
        """
        if not hasattr(self, "set_index"):
            self.set_index = 0
        if self.set_index >= len(self.random_splitted_functions):
            return None

        logger.info("Scheduling new random function set...")
        function_set = FunctionSet(self.random_splitted_functions[self.set_index])
        self.set_index += 1
        logger.info(
            f"New random function set scheduled, id {function_set.id}: \n{function_set}"
        )
        return function_set
