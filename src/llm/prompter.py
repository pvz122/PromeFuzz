"""
Prompter for LLM
"""

from loguru import logger
from abc import ABC, abstractmethod
import re
import json
from functools import cache

from src.utils import concat_excerpts
from src import vars as global_vars
from . import llm
from .rag import RAGExcerpt


class Prompter(ABC):
    """
    Prompt LLM for information
    """

    def __init__(self, llm_chat: llm.LLMChat):
        """
        Initialize prompter

        :param llm_chat: LLM chat
        """
        self.chat = llm_chat
        self.language_tag = (
            "c"
            if global_vars.library_language == global_vars.SupportedLanguages.C
            else "cpp"
        )
        self._load_prompt()

    @abstractmethod
    def _load_prompt(self): ...

    @abstractmethod
    def prompt(self): ...

    def set_system_prompt(self, system_prompt: str):
        """
        Set system prompt

        :param system_prompt: System prompt
        """
        self.chat.system_prompt = system_prompt

    @staticmethod
    @cache
    def _read_prompt(prompt_file_name: str) -> str:
        """
        Read prompt from file, cached

        :param prompt_file_name: Prompt file name
        :return: Prompt content
        """
        PROMPT_PATH = global_vars.promefuzz_path / "src" / "prompt"
        return (PROMPT_PATH / prompt_file_name).read_text()

    @staticmethod
    def parse_code_from_llm_output(response: str, warning: bool = True) -> str:
        """
        Parse ```LANGUAGE\nCODE\n``` from LLM output

        :param response: LLM output
        :return: Code
        """
        from parse import search

        code = search("```{lang}\n{code}\n```", response)
        code = (
            code if code else search("```\n{code}\n```", response)
        )  # try without language

        if code is None:
            if warning:
                logger.warning("No code found in LLM output")
                return ""
            else:
                return response
        return code["code"]

    @staticmethod
    def parse_indexes_from_llm_output(response: str, candidate_num: int) -> list[int]:
        """
        Parse indexes from LLM output, discard invalid indexes

        :param response: LLM output, indexes start from 1
        :param candidate_num: Number of candidates
        :return: Indexes, start from 0
        """
        indexes = re.findall(r"\d+", response)
        filtered_indexes = set()
        for index_str in indexes:
            index = int(index_str) - 1
            if index < 0:
                # 0 for none of the above
                continue
            if index >= candidate_num:
                logger.warning(
                    f"Index {index} from LLM output is out of range, discarding"
                )
                continue
            filtered_indexes.add(index)
        return list(filtered_indexes)

    @staticmethod
    def economize_prompt(prompt: str) -> str:
        """
        Remove unnecessary spaces and newlines from prompt to save token usage

        :param prompt: Prompt
        :return: Economized prompt
        """
        import re

        # replace all tabs with spaces
        prompt = prompt.replace("\t", " ")

        # remove trailing spaces at each line
        prompt = "\n".join([line.rstrip() for line in prompt.split("\n")])

        # consolidate more than 2 newlines to 2 newlines
        prompt = re.sub(r"\n{3,}", "\n\n", prompt)

        # consolidate more than 1 spaces to 1 spaces
        prompt = re.sub(r" {2,}", " ", prompt)

        return prompt

    @staticmethod
    def format_code(
        code: str,
        style: str = r"{BasedOnStyle: Google, ColumnLimit: 0, IndentWidth: 2, UseTab: Never}",
    ) -> str:
        """
        Format C/C++ code

        :param code: Code
        :return: Formatted code
        """
        import subprocess

        if not hasattr(Prompter, "clang_installed"):
            # detect clang-format
            try:
                subprocess.run(
                    ["clang-format", "--version"],
                    check=True,
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL,
                )
                Prompter.clang_installed = True
            except:
                logger.debug(f"clang-format not installed, will not format code")
                Prompter.clang_installed = False
        if not Prompter.clang_installed:
            return code

        # format code
        try:
            formatted_code = subprocess.run(
                ["clang-format", f"-style={style}"],
                input=code.encode(),
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            ).stdout.decode()
        except subprocess.CalledProcessError as e:
            logger.warning(f"Failed to format code: {e.stderr.decode()}")
            return code

        return formatted_code


class CGenPrompter(Prompter):
    def _load_prompt(self):
        """
        Load c generation prompt from file
        """
        self.system_prompt = self._read_prompt("generate_c_driver.sys")
        self.user_prompt = self._read_prompt("generate_c_driver.usr")
        self.function_template = self._read_prompt("generate_c_driver.sub")

    def prompt(
        self,
        gen_requirements,
    ) -> str:
        """
        Prompt LLM for C driver generation

        :param gen_requirements: Generation required information
        :return: Fuzz driver code
        """
        # import here to avoid circular import
        from src.generator.collector import CGenRequirements

        # type hint
        gen_requirements: CGenRequirements = gen_requirements

        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=gen_requirements.library_name,
            LIBRARY_PURPOSE=gen_requirements.library_purpose,
        )
        self.set_system_prompt(system_prompt)

        # make function strings
        if gen_requirements.api_order is not None:
            function_str = "You should invoke the functions in the following order: {}\n\nBelow is the detailed information:\n\n".format(
                " -> ".join(f"`{func}`" for func in gen_requirements.api_order)
            )
        else:
            function_str = ""
        function_str += "".join(
            self.function_template.format(
                INDEX=i,
                FUNCTION_NAME=func.name,
                FUNCTION_USAGE=func.usage,
                FUNCTION_SIGNATURE=self.format_code(func.signature),
            )
            for i, func in enumerate(gen_requirements.target_functions, start=1)
        )

        # set user prompt
        user_prompt = self.economize_prompt(
            self.user_prompt.format(
                LIBRARY_NAME=gen_requirements.library_name,
                TARGET_FUNCTIONS=function_str,
                DATA_DEFINITIONS=self.format_code(gen_requirements.data_definitions),
                HEADERS=gen_requirements.headers,
            )
        )

        fuzz_driver_code = self.chat.query(user_prompt)
        return self.parse_code_from_llm_output(fuzz_driver_code)


class CppGenPrompter(Prompter):
    def _load_prompt(self):
        """
        Load cpp generation prompt from file
        """

        self.system_prompt = self._read_prompt("generate_cpp_driver.sys")
        self.user_prompt = self._read_prompt("generate_cpp_driver.usr")
        self.function_template = self._read_prompt("generate_cpp_driver.sub")

    def prompt(
        self,
        gen_requirements,
    ) -> str:
        """
        Prompt LLM for C++ driver generation

        :param gen_requirements: Generation required information
        :return: Fuzz driver code
        """
        # import here to avoid circular import
        from src.generator.collector import CppGenRequirements

        # type hint
        gen_requirements: CppGenRequirements = gen_requirements

        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=gen_requirements.library_name,
            LIBRARY_PURPOSE=gen_requirements.library_purpose,
        )
        self.set_system_prompt(system_prompt)

        # make function strings
        if gen_requirements.api_order is not None:
            function_str = "You should invoke the functions in the following order: {}\n\nBelow is the detailed information:\n\n".format(
                " -> ".join(f"`{func}`" for func in gen_requirements.api_order)
            )
        else:
            function_str = ""
        EXPLANATION = "You should invoke all {} overloads above for this function."
        HELDBY_CLASS = "This function is a member of class {}. "
        function_str += "".join(
            self.function_template.format(
                INDEX=i,
                FUNCTION_NAME=func.name,
                FUNCTION_USAGE=func.usage,
                HELDBY_CLASS=(
                    HELDBY_CLASS.format(func.heldby_class) if func.heldby_class else ""
                ),
                FUNCTION_SIGNATURE=self.format_code(func.signature),
                EXPLANATION=(
                    EXPLANATION.format(func.signature_count)
                    if func.signature_count > 1
                    else ""
                ),
            )
            for i, func in enumerate(gen_requirements.target_functions, start=1)
        )

        # set user prompt
        user_prompt = self.economize_prompt(
            self.user_prompt.format(
                LIBRARY_NAME=gen_requirements.library_name,
                TARGET_FUNCTIONS=function_str,
                DATA_DEFINITIONS=self.format_code(gen_requirements.data_definitions),
                CONSTRUCTORS=self.format_code(gen_requirements.constructor_signatures),
                HEADERS=gen_requirements.headers,
            )
        )

        fuzz_driver_code = self.chat.query(user_prompt)
        return self.parse_code_from_llm_output(fuzz_driver_code)


class FixPrompter(Prompter):
    """
    Prompt LLM for fixing
    """

    # to be implemented by subclasses
    def _load_prompt(self): ...

    def prompt(self, error_message: str) -> str:
        """
        Prompt LLM for fixing

        :param error_message: Error message
        :return: Fixed code
        """
        user_prompt = self.fix_prompt.format(ERROR_MESSAGE=error_message)
        fixed_code = self.chat.query(user_prompt)
        return Prompter.parse_code_from_llm_output(fixed_code)


class FixBuildPrompter(FixPrompter):
    """
    Prompt LLM for fixing build error
    """

    def _load_prompt(self):
        """
        Load fix build prompt from file
        """
        self.fix_prompt = self._read_prompt("fix_build_error.usr")


class FixAsanPrompter(FixPrompter):
    """
    Prompt LLM for fixing ASAN error
    """

    def _load_prompt(self):
        """
        Load fix ASAN prompt from file
        """
        self.fix_prompt = self._read_prompt("fix_asan_error.usr")


class LibPurposePrompter(Prompter):
    """
    Prompter to deduce the purpose of a library
    """

    def _load_prompt(self):
        """
        Load deduce library purpose prompt
        """
        self.system_prompt = self._read_prompt("deduce_library_purpose.sys")
        self.user_prompt = self._read_prompt("deduce_library_purpose.usr")

    def prompt(self, library_name: str, document_excerpts: list[RAGExcerpt]) -> str:
        """
        Prompt LLM for deducing library purpose

        :param library_name: Name of the library
        :param document_excerpts: Excerpts from the library document
        :return: Deduced library purpose
        """
        # concatenate all excerpts
        excerpts_str = concat_excerpts(document_excerpts)

        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
        )
        self.set_system_prompt(system_prompt)

        # set user prompt
        user_prompt = self.user_prompt.format(
            LIBRARY_NAME=library_name,
            DOC_EXCERPTS=excerpts_str,
        )

        # query LLM
        summary = self.chat.query(user_prompt)

        return summary


class ValuableExcerptsPrompter(Prompter):
    """
    Prompter to select valuable excerpts for a certain function
    """

    def _load_prompt(self):
        """
        Load usable excerpts prompt
        """
        self.system_prompt = self._read_prompt("choose_valuable_excerpts.sys")
        self.user_prompt = self._read_prompt("choose_valuable_excerpts.usr")

    def prompt(
        self,
        library_name: str,
        function_name: str,
        document_excerpts: list[RAGExcerpt],
    ) -> list[int]:
        """
        Prompt LLM for selecting valuable excerpts

        :param library_name: Name of the library
        :param function_name: Name of the target function
        :param document_excerpts: Excerpts retrieved from the library document
        :return: Indexes of valuable excerpts
        """
        excerpt_str = concat_excerpts(document_excerpts)

        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
            FUNCTION_NAME=function_name,
        )
        self.set_system_prompt(system_prompt)

        # set user prompt
        user_prompt = self.user_prompt.format(
            DOC_EXCERPTS=excerpt_str,
        )

        # query LLM
        response = self.chat.query(user_prompt)

        # match all indexes of valuable excerpts
        indexes = self.parse_indexes_from_llm_output(response, len(document_excerpts))

        return indexes


class FuncUsageFromDocPrompter(Prompter):
    """
    Prompter to deduce the function usage from document excerpts and source code
    """

    def _load_prompt(self):
        """
        Load deduce function usage prompt
        """
        self.system_prompt = self._read_prompt("deduce_func_usage_from_doc.sys")
        self.user_prompt = self._read_prompt("deduce_func_usage_from_doc.usr")

    def prompt(
        self,
        library_name: str,
        function_name: str,
        function_signatures: str,
        function_source_code: str,
        document_excerpts: list[RAGExcerpt],
    ) -> str:
        """
        Prompt LLM for deducing function usage

        :param library_name: Name of the library
        :param function_name: Name of the function
        :param function_signatures: Signatures of the function
        :param function_source_code: Source code of the function
        :param document_excerpts: Excerpts from the library document
        :return: Deduced function usage
        """
        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
        )
        self.set_system_prompt(system_prompt)

        # set user prompt
        user_prompt = self.user_prompt.format(
            LANGUAGE_TAG=self.language_tag,
            FUNCTION_NAME=function_name,
            FUNCTION_SIGNATURES=self.format_code(function_signatures),
            FUNCTION_SOURCE_CODE=self.format_code(function_source_code),
            DOC_EXCERPTS=concat_excerpts(document_excerpts),
        )

        # query LLM
        response = self.chat.query(user_prompt)

        return response


class FuncUsageFromSrcPrompter(Prompter):
    """
    Prompter to deduce the function usage from source code
    """

    def _load_prompt(self):
        """
        Load deduce function usage prompt
        """
        self.system_prompt = self._read_prompt("deduce_func_usage_from_src.sys")
        self.user_prompt = self._read_prompt("deduce_func_usage_from_src.usr")

    def prompt(
        self,
        library_name: str,
        function_name: str,
        function_signatures: str,
        function_source_code: str,
    ) -> str:
        """
        Prompt LLM for deducing function usage

        :param library_name: Name of the library
        :param function_name: Name of the function
        :param function_signatures: Signatures of the function
        :param function_source_code: Source code of the function
        :return: Deduced function usage
        """
        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
        )
        self.set_system_prompt(system_prompt)

        # set user prompt
        user_prompt = self.user_prompt.format(
            LANGUAGE_TAG=self.language_tag,
            FUNCTION_NAME=function_name,
            FUNCTION_SIGNATURES=self.format_code(function_signatures),
            FUNCTION_SOURCE_CODE=self.format_code(function_source_code),
        )

        # query LLM
        response = self.chat.query(user_prompt)

        return response


class FuncRelevancePrompter(Prompter):
    """
    Prompter to determine the relevance of functions
    """

    def _load_prompt(self):
        """
        Load relevance prompt
        """
        self.system_prompt = self._read_prompt("choose_relevant_functions.sys")
        self.user_prompt = self._read_prompt("choose_relevant_functions.usr")
        self.candidate_template = self._read_prompt("choose_relevant_functions.sub")

    def prompt(
        self,
        library_name: str,
        library_purpose: str,
        target_function: tuple[str, str, str],
        candidate_functions: list[tuple[str, str, str]],
    ) -> list[int]:
        """
        Prompt LLM for determining the relevance of functions

        :param library_name: Name of the library
        :param library_purpose: Purpose of the library
        :param target_function: The target function, like: (name, purpose, signature)
        :param candidate_functions: The candidate functions, like: [(name, purpose, signature), ...]
        :return: Relevant function indexes in the candidate list
        """
        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
            LIBRARY_PURPOSE=library_purpose,
        )
        self.set_system_prompt(system_prompt)

        # make candidate functions string
        candidate_str = "".join(
            self.candidate_template.format(
                INDEX=i,
                FUNCTION_NAME=name,
                FUNCTION_PURPOSE=purpose,
                LANGUAGE_TAG=self.language_tag,
                FUNCTION_SIGNATURE=signature,
            )
            for i, (name, purpose, signature) in enumerate(candidate_functions, start=1)
        )

        # set user prompt
        user_prompt = self.user_prompt.format(
            TARGET_FUNCTION_NAME=target_function[0],
            TARGET_FUNCTION_PURPOSE=target_function[1],
            TARGET_FUNCTION_SIGNATURE=target_function[2],
            CANDIDATE_FUNCTIONS=candidate_str,
            LANGUAGE_TAG=self.language_tag,
        )

        # query LLM
        response = self.chat.query(user_prompt)

        # match all indexes of relevant functions
        indexes = self.parse_indexes_from_llm_output(response, len(candidate_functions))

        return indexes


class CrashConstraintPrompter(Prompter):
    """
    Prompter to learn constraints from crashes
    """

    def _load_prompt(self):
        """
        Load learn constraint prompt
        """
        self.system_prompt = self._read_prompt("learn_crash_constraint.sys")
        self.explaint_prompt = self._read_prompt("learn_crash_constraint_explain.usr")
        self.learn_prompt = self._read_prompt("learn_crash_constraint_learn.usr")
        self.fix_prompt = self._read_prompt("learn_crash_constraint_fix.usr")

    def prompt(
        self,
        crash_report: str,
        library_name: str,
        library_purpose: str,
        api_functions: list[str],
    ) -> tuple[dict[str, str], str]:
        """
        Prompt LLM for learning constraints from crashes

        :param crash_report: Crash report
        :param library_name: Name of the library
        :param library_purpose: Purpose of the library
        :param api_functions: Related API functions
        :return: Learned constraints and fixed fuzz driver code, like: ({api_function_name: constraint, ...}, fixed_fuzz_driver_code)
        """
        # prepare system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
            LIBRARY_PURPOSE=library_purpose,
        )
        self.set_system_prompt(system_prompt)

        # prepare explain prompt
        explain_prompt = self.explaint_prompt.format(
            CRASH_REPORT=crash_report,
        )

        # prepare learn prompt and fix prompt
        learn_prompt = self.learn_prompt.format(
            LIBRARY_NAME=library_name,
            RELATED_API_FUNCTIONS=", ".join(f"`{f}`" for f in api_functions),
        )
        fix_prompt = self.fix_prompt

        # query LLM
        # first query for explanation
        self.chat.query(explain_prompt)

        # then query for learning
        constraint_response = self.chat.query(learn_prompt)
        try:
            constraint = json.loads(
                self.parse_code_from_llm_output(constraint_response, warning=False)
            )
        except:
            constraint = {}

        # query for fixing
        if constraint:
            self.chat.remove_last_query()
            code_response = self.chat.query(fix_prompt)
            fixed_fuzz_driver_code = self.parse_code_from_llm_output(code_response)
        else:
            logger.warning(
                f"No constraint learned for crash, response: \n{constraint_response}"
            )
            fixed_fuzz_driver_code = ""

        return constraint, fixed_fuzz_driver_code


class CrashContraintReasoningPrompter(Prompter):
    """
    Prompter to learn constraints from crashes with reasoning model.
    For a reasoning model, we do not need to guide the LLM with CoT in the query.
    """

    def _load_prompt(self):
        """
        Load learn constraint prompt
        """
        self.system_prompt = self._read_prompt("learn_crash_constraint.sys")
        self.learn_prompt = self._read_prompt(
            "learn_crash_constraint_reasoning_model.usr"
        )
        self.fix_prompt = self._read_prompt("learn_crash_constraint_fix.usr")

    def prompt(
        self,
        crash_report: str,
        library_name: str,
        library_purpose: str,
        api_functions: list[str],
    ) -> tuple[dict[str, str], str]:
        """
        Prompt LLM for learning constraints from crashes

        :param crash_report: Crash report
        :param library_name: Name of the library
        :param library_purpose: Purpose of the library
        :param api_functions: Related API functions
        :return: Learned constraints and fixed fuzz driver code, like: ({api_function_name: constraint, ...}, fixed_fuzz_driver_code)
        """
        # prepare system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_NAME=library_name,
            LIBRARY_PURPOSE=library_purpose,
        )
        # it is recommended that no system prompt is set for reasoning model
        # self.set_system_prompt(system_prompt)

        # prepare learn prompt and fix prompt
        learn_prompt = self.learn_prompt.format(
            LIBRARY_NAME=library_name,
            RELATED_API_FUNCTIONS=", ".join(f"`{f}`" for f in api_functions),
            CRASH_REPORT=crash_report,
        )
        fix_prompt = self.fix_prompt

        # query LLM
        # first query for learning
        constraint_response = self.chat.query(system_prompt + "\n" + learn_prompt)
        try:
            constraint = json.loads(
                self.parse_code_from_llm_output(constraint_response, warning=False)
            )
        except:
            constraint = {}

        # query for fixing
        if constraint:
            code_response = self.chat.query(fix_prompt)
            fixed_fuzz_driver_code = self.parse_code_from_llm_output(code_response)
        else:
            logger.warning(
                f"No constraint learned for crash, response: \n{constraint_response}"
            )
            fixed_fuzz_driver_code = ""

        return constraint, fixed_fuzz_driver_code


class CrashAnalysisPrompter(Prompter):
    """
    Prompter to analyze crashes
    """

    def _load_prompt(self):
        """
        Load analyze crash prompt
        """
        self.system_prompt = self._read_prompt("analyze_crash.sys")
        self.user_prompt = self._read_prompt("analyze_crash.usr")

    def prompt(
        self, crash_report: str, library_purpose: str, library_name: str
    ) -> tuple[str, str]:
        """
        Prompt LLM for analyzing crashes

        :param crash_report: Crash report
        :param library_purpose: Purpose of the library
        :param library_name: Name of the library
        :return: Analysis from LLM and the reasoining content (if using reasoning model)
        """
        # set system prompt
        system_prompt = self.system_prompt.format(
            LIBRARY_PURPOSE=library_purpose,
            LIBRARY_NAME=library_name,
        )
        if isinstance(self.chat.client, llm.ReasoningLLMClient):
            # For reasoning model, it is recommended that no system prompt is set
            user_prompt = system_prompt + "\n"
        else:
            user_prompt = ""
            self.set_system_prompt(system_prompt)

        # set user prompt
        user_prompt += self.user_prompt.format(
            CRASH_REPORT=crash_report,
        )

        # query LLM
        return self.chat.query_reasoning(user_prompt)
