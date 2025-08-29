"""
Generate Fuzz Driver
"""

from pathlib import Path
from loguru import logger

from src import vars as global_vars
from src.preprocessor.information import InfoRepository
from src.preprocessor.consumer import OrderSet
from src.comprehender.comprehender import LibraryComprehension
from src.llm.llm import LLMClient, LLMChat
from src.llm.prompter import CGenPrompter, CppGenPrompter
from .collector import CInfoCollector, CppInfoCollector
from .driver import FuzzDriver
from .scheduler import FunctionSet


class Generator:
    """
    Class to generate fuzz driver
    """

    C_BASIC_HEADERS = ["stdint.h", "stddef.h", "string.h", "stdlib.h", "stdio.h"]
    CPP_BASIC_HEADERS = [
        "iostream",
        "sstream",
        "string",
        "vector",
        "cstring",
        "cstdlib",
        "cstdio",
        "cstdint",
        "cstddef",
    ]

    def __init__(
        self, llm_client: LLMClient, info_repo: InfoRepository, comprehension: LibraryComprehension
    ):
        """
        Initialize the generator

        :param llm_client: LLM client
        :param info_repo: Information repository from preprocessor
        :param comprehension: Library comprehension
        """
        self.llm_client = llm_client
        self.info_repo = info_repo
        self.comprehension = comprehension

    def _finishing_generation(self, fuzz_driver_code: str) -> str:
        """
        Some finishing work after generation

        :param fuzz_driver_code: The generated fuzz driver code
        :return: The modified fuzz driver code
        """
        # write basic headers
        BASIC_HEADERS = (
            self.C_BASIC_HEADERS
            if global_vars.library_language == global_vars.SupportedLanguages.C
            else self.CPP_BASIC_HEADERS
        )
        fuzz_driver_code = (
            f"#include <{'>\n#include <'.join(BASIC_HEADERS)}>\n" + fuzz_driver_code
        )

        return fuzz_driver_code

    def _override_chat_history(self, fuzz_driver_code: str, llm_chat: LLMChat):
        """
        Override the LLM generated code response in the chat history

        :param fuzz_driver_code: The generated fuzz driver code
        """
        language = (
            "cpp"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else "c"
        )
        new_history = llm_chat.history.copy()
        new_history[-1] = {
            "role": "assistant",
            "content": f"```{language}\n{fuzz_driver_code}\n```",
        }
        llm_chat.history = new_history

    def generate(self, target_functions: FunctionSet | OrderSet) -> FuzzDriver:
        """
        Generate fuzz driver using LLM for the given target functions

        :param target_functions: The selected target functions, could be a normal function set or an order set
        :return: The generated fuzz driver
        """
        if isinstance(target_functions, OrderSet):
            function_set = target_functions.as_function_set
        else:
            function_set = target_functions

        # subtract the remaining generation rounds
        function_set.remain_gen_rounds -= 1
        logger.info(
            f"Generating fuzz driver for function set {function_set.id}, remaining rounds: {function_set.remain_gen_rounds}"
        )

        # set language specific classes
        new_chat = LLMChat(self.llm_client)
        if global_vars.library_language == global_vars.SupportedLanguages.C:
            collector = CInfoCollector(self.info_repo, self.comprehension)
            prompter = CGenPrompter(new_chat)
        elif global_vars.library_language == global_vars.SupportedLanguages.CPP:
            collector = CppInfoCollector(self.info_repo, self.comprehension)
            prompter = CppGenPrompter(new_chat)

        # collect information
        collected_info = collector.collect(target_functions)

        # prompt for generation
        fuzz_driver_code = prompter.prompt(collected_info)
        if not fuzz_driver_code:
            logger.error(
                f"Failed to generate fuzz driver for function set {function_set.id} during prompting"
            )
            return None

        # finishing work
        fuzz_driver_code = self._finishing_generation(fuzz_driver_code)
        self._override_chat_history(fuzz_driver_code, new_chat)

        logger.debug(f"Generated code: \n{fuzz_driver_code}")

        # create fuzz driver
        new_driver = FuzzDriver(fuzz_driver_code, new_chat, target_functions)
        new_driver.query_count += 1

        logger.info(f"New fuzz driver generated, ID {new_driver.id}")
        return new_driver
