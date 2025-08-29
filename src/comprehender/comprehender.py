"""
Comprehend the library

INPUT: document retriever, api function names and signatures
OUTPUT: library purpose, function usage, function relevance
1. Retrieve to obtain the library purpose.
2. For each API function, retrieve its usage. Provide the retrieved document excerpts to the LLM,
and ask it whether these describe the usage of a certain function.
If they do, ask the LLM to describe the function's usage based on documents and source code.
3. For API functions without documentation, use the LLM to infer the usage based on source code.
4. Provide the LLM with the signature and usage of each function, and let it select relevant functions.
"""

from abc import ABC, abstractmethod
from pathlib import Path
from tqdm import tqdm
from loguru import logger
from functools import cached_property
from dataclasses import dataclass, asdict
import pickle
import json
from concurrent.futures import ThreadPoolExecutor
import threading
import time

from src.utils import concat_excerpts, with_progress_update
from src import vars as global_vars
from src.llm.llm import LLMClient, LLMChat
from src.llm.prompter import (
    LibPurposePrompter,
    ValuableExcerptsPrompter,
    FuncUsageFromDocPrompter,
    FuncUsageFromSrcPrompter,
    FuncRelevancePrompter,
)
from src.preprocessor.information import InfoRepository, FunctionInfo
from src.preprocessor.api import APICollection
from src.preprocessor.relevance import Relevance
from .knowledge import Knowledge, RAGExcerpt


class Comprehender(ABC):
    """
    Base class for comprehenders
    """

    # pool size for parallel processing
    pool_size: int = 1

    @cached_property
    def comprehension(self):
        return self.comprehend()

    @abstractmethod
    def comprehend(self): ...


@dataclass
class LibraryComprehension:
    """
    Dataclass to store the library comprehension
    """

    purpose: str
    """
    Library purpose
    """

    functions: dict[str, str]
    """
    Function comprehensions about their usage
    as function name: function usage
    """

    def dump(self, path: Path):
        """
        Dump the library comprehension to a file

        :param path: Path to dump the library comprehension
        """
        with open(path, "wb") as f:
            pickle.dump(self, f)

    def dump_json(self, path: Path):
        """
        Dump the library comprehension to a JSON file, only for human-readable purpose

        :param path: Path to dump the library comprehension
        """

        class CompJSONEncoder(json.JSONEncoder):
            def default(self, o):
                if isinstance(o, LibraryComprehension):
                    return asdict(o)
                else:
                    return super().default(o)

        with open(path, "w") as f:
            json.dump(self, f, cls=CompJSONEncoder, indent=4)

    @classmethod
    def load(cls, path: Path) -> "LibraryComprehension":
        """
        Load the library comprehension from a file

        :param path: Path to load the library comprehension
        :return: The library comprehension
        """
        with open(path, "rb") as f:
            return pickle.load(f)


class GeneralComprehender(Comprehender):
    """
    Comprehend all the information about the library, used to invoke all the comprehenders
    """

    # flags to control the comprehender
    DO_LIBRARY_PURPOSE = True
    DO_FUNC_USAGE = True
    DO_FUNC_RELEVANCE = True

    def __init__(
        self,
        llm_client: LLMClient,
        knowledge: Knowledge,
        api_collection: APICollection,
        info_repo: InfoRepository,
        pool_size: int = 1,
    ):
        """
        Initialize the general comprehender

        :param llm_client: LLM client
        :param knowledge: Document knowledge
        :param api_collection: API functions
        :param info_repo: Information repository from preprocess
        :param pool_size: Number of processes to use for comprehension
        """
        self.llm_client = llm_client
        self.knowledge = knowledge
        self.api_collection = api_collection
        self.info_repo = info_repo

        Comprehender.pool_size = pool_size

        self.lib_comprehension = LibraryComprehension("", {})
        self.func_relevance = None

    def comprehend(self) -> tuple[LibraryComprehension, "SemanticRelevance"]:
        """
        Comprehend the library

        :return: Library comprehension and function relevance
        """
        # comprehend the library purpose
        if self.DO_LIBRARY_PURPOSE:
            logger.info("Comprehending library purpose...")
            lib_purpose_comprehender = LibPurposeComprehender(
                self.llm_client, self.knowledge
            )
            self.lib_comprehension.purpose = lib_purpose_comprehender.comprehension
            logger.success(
                f"Library purpose comprehended: {self.lib_comprehension.purpose}"
            )

        # comprehend the function usage
        if self.DO_FUNC_USAGE:
            logger.info("Comprehending function usage...")
            func_usage_comprehender = FuncUsageComprehender(
                self.llm_client,
                self.knowledge,
                self.api_collection,
                self.info_repo,
            )
            self.lib_comprehension.functions = func_usage_comprehender.comprehension
            logger.success("Function usage comprehended")

        # comprehend the function relevance
        if self.DO_FUNC_RELEVANCE:
            logger.info("Comprehending function relevance...")
            func_relevance_comprehender = FuncRelevanceComprehender(
                self.llm_client,
                self.api_collection,
                self.info_repo,
                self.lib_comprehension.purpose,
                self.lib_comprehension.functions,
            )
            self.func_relevance = func_relevance_comprehender.comprehend()
            logger.success("Function relevance comprehended")

        return self.lib_comprehension, self.func_relevance

    def dump(self, comprehension_path: Path | None, relevance_path: Path | None):
        """
        Dump the library comprehension and function relevance to files

        :param comprehension_path: Path to dump the library comprehension, set to None to skip
        :param relevance_path: Path to dump the function relevance, set to None to skip
        """
        if comprehension_path is not None:
            if (
                not self.lib_comprehension.purpose
                and not self.lib_comprehension.functions
            ):
                raise ValueError("Comprehension not done yet")
            self.lib_comprehension.dump(comprehension_path)

        if relevance_path is not None:
            if not self.func_relevance:
                raise ValueError("Function relevance not done yet")
            self.func_relevance.dump(relevance_path)

    def dump_to_json_csv(
        self, comprehension_path: Path | None, relevance_path: Path | None
    ):
        """
        Dump the library comprehension to JSON and function relevance to CSV.
        Only for human-readable purpose, not for loading back.

        :param comprehension_path: Path to dump the library comprehension, set to None to skip
        :param relevance_path: Path to dump the function relevance, set to None to skip
        """
        if comprehension_path is not None:
            if (
                not self.lib_comprehension.purpose
                and not self.lib_comprehension.functions
            ):
                raise ValueError("Comprehension not done yet")
            self.lib_comprehension.dump_json(comprehension_path)

        if relevance_path is not None:
            if not self.func_relevance:
                raise ValueError("Function relevance not done yet")
            self.func_relevance.dump_csv(relevance_path)


class LibPurposeComprehender(Comprehender):
    """
    Comprehend the purpose of the library

    IN: document knowledge
    OUT: library purpose
    """

    RETRIEVE_TEMPLATE = "introduction of the {} library"

    def __init__(self, llm_client: LLMClient, knowledge: Knowledge):
        """
        Initialize the library purpose comprehender

        :param llm_client: LLM client
        :param knowledge: Document knowledge
        """
        self.llm_client = llm_client
        self.library_name = global_vars.library_name
        self.knowledge = knowledge

    def comprehend(self) -> str:
        """
        Comprehend the purpose of the library

        :return: concise description of the library
        """
        # retrieve the document
        document_excerpts = self.knowledge.retrieve(
            self.RETRIEVE_TEMPLATE.format(self.library_name)
        )

        # prompt for library purpose
        prompter = LibPurposePrompter(LLMChat(self.llm_client))
        library_purpose = prompter.prompt(self.library_name, document_excerpts)

        if not library_purpose:
            raise ValueError("No response from the LLM")
        logger.debug(f"Library purpose: \n{library_purpose}")

        return library_purpose


class FuncUsageComprehender(Comprehender):
    """
    Comprehend the usage of the function

    IN: document knowledge, library purpose, function names, function signatures, function source code
    OUT: function usage
    """

    # Whether to comprehend the function usage from the document
    # If set to False, all the function purposes will be inferred from the source code
    COMPREHEND_FROM_DOC = False

    # The message used to retrieve the vector database
    RETRIEVE_TEMPLATE = "usage of function {}"

    # If a function is below this threshold, we provide the whole function implementation
    PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD = 30

    def __init__(
        self,
        llm_client: LLMClient,
        knowledge: Knowledge,
        api_collection: APICollection,
        info_repo: InfoRepository,
    ):
        """
        Initialize the function purpose comprehender

        :param llm_client: LLM client
        :param knowledge: Document knowledge
        :param api_collection: API functions
        :param info_repo: Information repository from preprocess
        """
        self.library_name = global_vars.library_name
        self.llm_client = llm_client
        self.knowledge = knowledge
        self.api_collection = api_collection
        self.info_repo = info_repo

    @staticmethod
    def _get_function_signatures(
        function_name: str, api_collection: APICollection, info_repo: InfoRepository
    ) -> str:
        """
        Get the function signature by function name

        :param function_name: Function name
        :param api_collection: API functions
        :param info_repo: Information repository from preprocess
        :return: Function signature
        """
        func_locs = api_collection.get_locations_by_name(function_name)
        if not func_locs:
            raise ValueError(f"Function {function_name} not found")

        func_sigs = []
        for loc in func_locs:
            func_info: FunctionInfo = info_repo.get_info(loc, FunctionInfo)
            if func_info is None:
                raise ValueError(f"Function info not found for {loc}")
            func_sigs.append(func_info.signature)

        return "\n".join(func_sigs)

    def _get_function_source(self, function_name: str) -> str:
        """
        Get the function source code by function name

        :param function_name: Function name
        :return: Function source code
        """
        func_locs = self.api_collection.get_locations_by_name(function_name)
        if not func_locs:
            raise ValueError(f"Function {function_name} not found")

        func_loc = func_locs[0]
        code = (
            ""
            if len(func_locs) == 1
            else f"// One of the overload of {function_name}\n"
        )  # this function name has several overloads, simply choose the first one to provide source

        # get the function implementation range
        func_impl_start_pos, func_impl_end_pos = self.info_repo.get_info(func_loc, FunctionInfo).impl_range
        if func_impl_start_pos is None or func_impl_end_pos is None:
            logger.error(f"Function implementation range not found for {function_name}")
            return ""
        func_impl_end_pos += 1 # for the last "}" character

        # slice the function implementation
        if (
            func_impl_end_pos.line - func_impl_start_pos.line
            < self.PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD
        ):
            code += func_impl_start_pos.get_content_till_pos(func_impl_end_pos)
        else:
            func_impl_end_pos = func_impl_start_pos.copy()
            func_impl_end_pos.set_to_start_of_line()
            func_impl_end_pos.line += (
                self.PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD
            )
            code += func_impl_start_pos.get_content_till_pos(func_impl_end_pos)
            code += "// some code omitted...\n"

        return code

    @with_progress_update
    def _comprehend_one_function(
        self,
        func_name: str,
        func_excerpts: list[RAGExcerpt] = None,
        progress: tqdm = None,
    ) -> tuple[str, str]:
        """
        Comprehend the usage of one function

        :param func_name: Function name
        :param func_excerpts: Document excerpts of the function
        :param progress: Progress bar object
        :return: Function usage, as a tuple of (function name, function usage)
        """
        # get the function signatures and source code
        try:
            func_sigs = self._get_function_signatures(
                func_name, self.api_collection, self.info_repo
            )
        except ValueError as e:
            logger.error(f"Could not get function signature for {func_name}: {e}")
            return (func_name, "")
        func_source = self._get_function_source(func_name)

        if self.COMPREHEND_FROM_DOC and func_excerpts is not None:
            # determine the valuable document excerpts
            prompter = ValuableExcerptsPrompter(LLMChat(self.llm_client))
            valuable_indexes = prompter.prompt(
                self.library_name, func_name, func_excerpts
            )
            if valuable_indexes:
                # this function has valuable document excerpts
                # infer the usage based on the document excerpts
                valuable_excerpts = [func_excerpts[i] for i in valuable_indexes]
                logger.debug(
                    f"Valuable document excerpts for {func_name}: \n{concat_excerpts(valuable_excerpts)}"
                )

                # prompt for function usage
                prompter = FuncUsageFromDocPrompter(LLMChat(self.llm_client))
                usage = prompter.prompt(
                    self.library_name,
                    func_name,
                    func_sigs,
                    func_source,
                    valuable_excerpts,
                )

                logger.debug(f"{func_name} comprehended with documentation:\n{usage}")
                return (func_name, usage)
            else:
                # this function has no valuable document excerpts
                # infer the purpose based on the source code
                logger.debug(f"Function {func_name} has no valuable document excerpts")

        # prompt for function usage
        prompter = FuncUsageFromSrcPrompter(LLMChat(self.llm_client))
        usage = prompter.prompt(self.library_name, func_name, func_sigs, func_source)

        logger.debug(f"{func_name} comprehended without documentation: \n{usage}")
        return (func_name, usage)

    def comprehend(self) -> dict[str, str]:
        """
        Comprehend the usage of the function

        :return: Function comprehensions, as function name: function usage
        """
        # Algorithm:
        # 1. Get all API function names as targets
        # XXX Because the retriever can only identify function names but not their locations/signatures,
        # XXX we need to use the API function names to retrieve and comprehend the function.
        # XXX This relies on the assumption that the overloaded functions with the same name have
        # XXX the same purpose and usage.
        # 2. Retrieve the document excerpts for each function name
        # 3. Prompt the LLM to determine which document excerpts describe the usage of the function
        # 4. If the LLM finds a match, prompt the LLM with document excerpts and source code to infer the usage
        # 5. If the LLM does not find a match, prompt the LLM with source code to infer the usage

        # get all function names, deduplicated
        function_names = self.api_collection.function_names

        excerpts = dict()
        if self.COMPREHEND_FROM_DOC:
            # retrieve the document excerpts for each function name
            for func in tqdm(
                function_names,
                desc="Retrieving function usage",
                unit="function",
                colour="BLUE",
                leave=False,
            ):
                excerpts[func] = self.knowledge.retrieve(
                    self.RETRIEVE_TEMPLATE.format(func)
                )

        # comprehend the function usage
        progress_bar = tqdm(
            total=len(function_names),
            desc="Comprehending function usage",
            unit="function",
            colour="BLUE",
            leave=False,
        )
        if self.pool_size > 1:
            with ThreadPoolExecutor(max_workers=self.pool_size) as executor:
                results = list(
                    executor.map(
                        lambda func: self._comprehend_one_function(
                            func, excerpts.get(func, None), progress=progress_bar
                        ),
                        function_names,
                    )
                )
        else:
            results = [
                self._comprehend_one_function(
                    func, excerpts.get(func, None), progress=progress_bar
                )
                for func in function_names
            ]

        progress_bar.close()
        return {result[0]: result[1] for result in results}


class SemanticRelevance(Relevance):
    """
    Class to store the semantic relevance of the API functions
    """

    def _calc_relevance(self):
        """
        Because semantic relevance is updated through comprehension, this method is left empty
        """
        pass


class FuncRelevanceComprehender(Comprehender):
    """
    Comprehend the relevance of the function

    IN: library purpose, function purposes, function signatures
    OUT: function relevance
    """

    FUNCTION_BATCH_SIZE = 24

    def __init__(
        self,
        llm_client: LLMClient,
        api_collection: APICollection,
        info_repo: InfoRepository,
        library_purpose: str,
        function_usage: dict[str, str],
    ):
        """
        Initialize the function relevance comprehender

        :param llm_client: LLM client
        :param api_collection: API functions
        :param info_repo: Information repository from preprocess
        :param library_purpose: Purpose of the library from the library purpose comprehender
        :param function_usage: Function usage from the function usage comprehender
        """
        self.library_name = global_vars.library_name
        self.llm_client = llm_client
        self.api_collection = api_collection
        self.info_repo = info_repo
        self.library_purpose = library_purpose
        self.function_usage = function_usage

        # initialize the relevance
        self.relevance = SemanticRelevance(api_collection)

    def _get_function_usage_and_signature(
        self,
        function_name: str,
        function_usage: dict[str, str],
    ) -> tuple[str, str, str]:
        """
        Get the function purpose and signature by function name

        :param function_name: Function name
        :param function_usage: Function usage
        :return: A tuple of (function name, function usage, function signature)
        """
        function_usage = function_usage.get(function_name, "")
        function_signature = FuncUsageComprehender._get_function_signatures(
            function_name, self.api_collection, self.info_repo
        )
        return (
            function_name,
            function_usage,
            function_signature,
        )

    def _set_relevance_safe(self, target_func_loc, relevant_func_loc):
        """
        Set relevance of two functions to 1, thread-safe

        :param target_func_loc: Location of the target function
        :param relevant_func_loc: Location of the relevant function
        """
        if self.pool_size > 1:
            if not hasattr(self, "relevance_lock"):
                self.relevance_lock = threading.Lock()
            with self.relevance_lock:
                self.relevance.set_relevance(target_func_loc, relevant_func_loc, 1)
        else:
            self.relevance.set_relevance(target_func_loc, relevant_func_loc, 1)

    def _comprehend_one_target_wrapper(
        self, target_func: str, candidate_funcs: list[str], progress: tqdm = None
    ):
        """
        Call _comprehend_one_target with progress update
        """
        self._comprehend_one_target(target_func, candidate_funcs)
        if progress is not None:
            progress.update(len(candidate_funcs))

    def _comprehend_one_target(self, target_func: str, candidate_funcs: list[str]):
        """
        Run the prompter for one target function to get the relevant functions, set the relevance

        :param target_func: The target function name
        :param candidate_funcs: The candidate function names
        """
        if not candidate_funcs:
            return

        # get target function tuple
        try:
            target_function_tuple = self._get_function_usage_and_signature(
                target_func, self.function_usage
            )
        except ValueError as e:
            logger.error(
                f"Could not get function usage and signature for {target_func}: {e}"
            )
            return

        # get candidate functions tuples
        candidate_function_tuples = []
        for func in candidate_funcs:
            try:
                candidate_function_tuples.append(
                    self._get_function_usage_and_signature(
                        func,
                        self.function_usage,
                    )
                )
            except ValueError as e:
                logger.error(
                    f"Could not get function usage and signature for {func}: {e}"
                )
                return

        # prompt for relevance
        prompter = FuncRelevancePrompter(LLMChat(self.llm_client))
        relevant_func_indexes = prompter.prompt(
            self.library_name,
            self.library_purpose,
            target_function_tuple,
            candidate_function_tuples,
        )
        logger.debug(
            'Relevant functions for "{}": \n{}'.format(
                target_func,
                ", ".join(
                    func
                    for i, func in enumerate(candidate_funcs)
                    if i in relevant_func_indexes
                ),
            )
        )

        # get function locations
        target_func_locs = self.api_collection.get_locations_by_name(target_func)
        relevant_func_locs = []
        for index in relevant_func_indexes:
            relevant_func_locs.extend(
                self.api_collection.get_locations_by_name(candidate_funcs[index])
            )

        # set relevance
        for target_func_loc in target_func_locs:
            for relevant_func_loc in relevant_func_locs:
                self._set_relevance_safe(target_func_loc, relevant_func_loc)

    def _create_batch(self, target_func: str, candidate_funcs: list[str]):
        """
        The generator to emit a batch of target function and candidate functions

        :param target_func: The target function name
        :param candidate_funcs: Locations of the candidate functions
        :return: The parameters for invoking _comprehend_one_target_wrapper
        """
        # set up progress bar
        progress_bar = tqdm(
            desc=f"Comprehending {target_func}",
            unit="candidate function",
            colour="GREEN",
            total=len(candidate_funcs),
            leave=False,
        )

        # yield the parameters
        for i in range(0, len(candidate_funcs), self.FUNCTION_BATCH_SIZE):
            yield target_func, candidate_funcs[
                i : i + self.FUNCTION_BATCH_SIZE
            ], progress_bar

    def comprehend(self) -> SemanticRelevance:
        """
        Comprehend the relevance of the function

        :return: Functionality relevance of the API functions
        """
        function_names = self.api_collection.function_names
        executor = (
            ThreadPoolExecutor(max_workers=self.pool_size)
            if self.pool_size > 1
            else None
        )

        for i, target_func in tqdm(
            enumerate(function_names),
            desc="Comprehending function relevance",
            unit="function",
            colour="BLUE",
            total=len(function_names),
            leave=False,
        ):
            candidate_funcs = function_names[i + 1 :]
            for batch in self._create_batch(target_func, candidate_funcs):
                if executor:
                    executor.submit(self._comprehend_one_target_wrapper, *batch)
                    # if the pool is full, wait for one task to finish
                    while executor._work_queue.qsize() > self.pool_size:
                        time.sleep(0.1)
                else:
                    self._comprehend_one_target_wrapper(*batch)

        if executor:
            executor.shutdown(wait=True)
        return self.relevance
