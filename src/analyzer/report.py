"""
Compose crash report for ASan error.
"""

from loguru import logger
from random import choice
from pathlib import Path
from typing import List

from src import vars as global_vars
from src.utils import FilePos, is_source_file
from src.preprocessor.information import InfoRepository, FunctionInfo
from src.preprocessor.api import APICollection
from src.comprehender.comprehender import LibraryComprehension
from src.generator.scheduler import FunctionSet
from src.generator.collector import CInfoCollector, CppInfoCollector
from .asan import AsanError, AsanTrace


class CrashReportComposer:
    """
    Class to compose crash report for ASan error.
    """

    # The template of the crash report
    TEMPLATE = """# Fuzz driver

```{LANGUAGE_TAG}
{DRIVER_CODE}
```

# Crash report

## Crash reason

{CRASH_REASON}

## Backtrace

```
{BACKTRACE}
```

## Related source code

Part of the {LIBRARY_NAME} library that is relevant to the crash is as follows:

{LIBRARY_CODE}

## Related data definitions

```{LANGUAGE_TAG}
{DATA_DEFINITIONS}
```"""
    # If a function is below this threshold, we provide the whole function implementation
    PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD = 30

    def __init__(
        self,
        info_repo: InfoRepository,
        api_collection: APICollection,
    ):
        """
        initialize the crash report composer.

        :info_repo: Information repository from preprocessor
        :param api_collection: API collection from preprocessor
        """
        self.info_repo = info_repo
        self.api_collection = api_collection

        # we don't need comprehension in crash report, thus using an empty comprehension
        if global_vars.library_language == global_vars.SupportedLanguages.C:
            self.info_collector = CInfoCollector(
                info_repo, LibraryComprehension("", {})
            )
        else:
            self.info_collector = CppInfoCollector(
                info_repo, LibraryComprehension("", {})
            )

    def compose_and_get_related_api_functions(
        self, asan_error: AsanError, fuzz_driver_code: str
    ) -> tuple[str, FunctionSet]:
        """
        Compose the crash report for an ASan error and get the related API functions.
        Used in learning mode.

        :param asan_error: The ASan error
        :param fuzz_driver_code: The fuzz driver code that causes the crash
        :return: The crash report and the related API functions
        """
        return self.compose(
            asan_error, fuzz_driver_code
        ), self._get_related_api_functions(self._get_related_functions(asan_error))

    def compose_with_inferred_fuzz_driver_code(self, asan_error: AsanError) -> str:
        """
        Compose the crash report for an ASan error with inferred fuzz driver code.
        Used in analysis mode.

        :param asan_error: The ASan error
        :return: The crash report
        """
        fuzz_driver_code = self._infer_fuzz_driver_code(asan_error)
        return self.compose(asan_error, fuzz_driver_code)

    def compose(self, asan_error: AsanError, fuzz_driver_code: str) -> str:
        """
        Compose the crash report for an ASan error.

        :param asan_error: The ASan error
        :param fuzz_driver_code: The fuzz driver code that causes the crash
        :return: The crash report
        """
        related_functions = self._get_related_functions(asan_error)
        related_api_functions = self._get_related_api_functions(related_functions)
        backtrace = self._collect_backtrace(asan_error)
        library_code = self._collect_library_code(related_functions)
        data_definitions = self._collect_data_defs(related_api_functions)
        language_tag = (
            "c"
            if global_vars.library_language == global_vars.SupportedLanguages.C
            else "cpp"
        )
        return self.TEMPLATE.format(
            LANGUAGE_TAG=language_tag,
            DRIVER_CODE=fuzz_driver_code,
            CRASH_REASON=asan_error.error_reason,
            BACKTRACE=backtrace,
            LIBRARY_NAME=global_vars.library_name,
            LIBRARY_CODE="\n\n".join(
                f"- `{name}`:\n```{language_tag}\n{code}\n```"
                for name, code in library_code.items()
            ),
            DATA_DEFINITIONS=data_definitions,
        )

    def _infer_fuzz_driver_code(self, asan_error: AsanError) -> str:
        """
        Infer the fuzz driver code from the ASan error stack trace.

        :param asan_error: The ASan error
        :return: The inferred fuzz driver code
        """
        # get the LLVMFuzzerTestOneInput functions
        fuzzer_funcs: dict[str, FilePos] = dict()
        for tb in asan_error.tracebacks:
            for t in tb.traces:
                if (
                    t.function.startswith("LLVMFuzzerTestOneInput")
                    and t.file_pos is not None
                ):
                    fuzzer_funcs[t.function] = t.file_pos
        if not fuzzer_funcs:
            logger.error(
                "No LLVMFuzzerTestOneInput function found in the backtrace, can not read the fuzz driver code"
            )
            return ""

        # in synthesized driver, we will get LLVMFuzzerTestOneInput and LLVMFuzzerTestOneInput_xxx
        # use LLVMFuzzerTestOneInput_xxx
        fuzzer_func_name = None
        for func_name in fuzzer_funcs.keys():
            if func_name.startswith("LLVMFuzzerTestOneInput_"):
                fuzzer_func_name = func_name
                break
        if fuzzer_func_name is None:
            fuzzer_func_name = next(iter(fuzzer_funcs.keys()))
        fuzzer_func_pos = fuzzer_funcs[fuzzer_func_name]

        # search for func_name upwards from the file_pos
        fuzzer_func_pos = fuzzer_func_pos.find_str(func_name, is_backward=True)
        fuzzer_func_pos.set_to_start_of_line()

        # search for the "{" after the fuzzer_func_pos
        bracket_pos = fuzzer_func_pos.find_str("{", is_backward=False)

        # search for the "}" that matches the "{" after the fuzzer_func_pos
        remain_bracket = 0
        for cur_pos in bracket_pos.walk():
            if cur_pos.cur_char == "{":
                remain_bracket += 1
            elif cur_pos.cur_char == "}":
                remain_bracket -= 1
                if remain_bracket == 0:
                    break
        else:
            logger.error(
                f"Failed to find the end of the {fuzzer_func_name} function in {fuzzer_func_pos.file}"
            )
            return ""

        # slice the code
        return fuzzer_func_pos.get_content_till_pos(cur_pos + 1)

    def _collect_backtrace(self, asan_error: AsanError) -> str:
        """
        Collect the backtrace of an ASan error.

        :param asan_error: The ASan error
        :return: The backtrace
        """
        backtrace = ""
        for tb in asan_error.tracebacks:
            backtrace += tb.description + "\n\n"
            for t in tb.traces:
                backtrace += f"#{t.number} {t.function}"
                if (pos := t.file_pos) is not None:
                    backtrace += "\n" + pos.human_str
                backtrace += "\n\n"
                if t.function.startswith("LLVMFuzzerTestOneInput"):
                    # omit the call stack before LLVMFuzzerTestOneInput
                    break
            backtrace += "\n"
        return backtrace.strip()

    def _get_function_loc(self, func_name: str, file_loc: str | None) -> str | None:
        """
        Get the location of a function in the extracted library meta data.
        This location identifies the function.
        If `file_loc` is None, which means the file location is not available
        (missing in the trace because the library is not compiled with debug info),
        a random location of the functions with the same name will be returned.

        :param func_name: The function name
        :param file_loc: The file location
        :return: The function location, None if not found
        """
        # get the functions with the same name
        funcs: List[FunctionInfo] = self.info_repo.get_info_by_name(
            func_name, FunctionInfo
        )
        if not funcs:
            logger.warning(
                f"Function {func_name} in the backtrace not found in the library meta data"
            )
            return None
        list_func_locs = [func.location for func in funcs]

        if file_loc is None:
            if len(list_func_locs) == 1:
                return list_func_locs[0]
            # random choose one
            # XXX: This is not good anyway, we strongly recommend to compile the library with debug info
            logger.warning(
                f"File location of function {func_name} in the backtrace is not available, randomly choose one. Please compile the library with debug info!"
            )
            return choice(list_func_locs)
        else:
            # check which function contains the file location
            try:
                file_pos = FilePos.from_location_line(file_loc)
            except ValueError:
                logger.error(f"Invalid file location: {file_loc}")
                return None

            for func in funcs:
                func_start, func_end = func.impl_range

                # must be in the same file
                if func_start.file != file_pos.file:
                    continue

                # function loc range contains the file pos
                if func_start <= file_pos <= func_end:
                    return func.location

            # not found
            logger.warning(
                f"Function {func_name} with file location {file_loc} not found in the library meta data"
            )
            return None

    def _get_related_functions(
        self, asan_error: AsanError
    ) -> list[tuple[str, str, str]]:
        """
        Get the related functions of an ASan error.

        :param asan_error: The ASan error
        :return: The related functions, as a list of tuples of (function name, file location in backtrace, function location as ID)
        """

        def _get_file_from_non_source_trace(
            trace: AsanTrace,
        ) -> Path | None:
            return Path(trace.location.split("+")[0]) if "+" in trace.location else None

        def _process_function_name(func_name: str) -> str | None:
            # FIXME: Maybe we should reconsider the filtering strategy
            # exclude_prefixes = ["_", "operator"]
            # if any(func_name.startswith(prefix) for prefix in exclude_prefixes):
            #     return None

            # remove args
            func_name = func_name.split("(")[0].strip()
            return func_name

        related_functions = []
        for tb in asan_error.tracebacks:
            for t in tb.traces:
                pos = t.file_pos
                if pos is not None and (pos.file):
                    if func_name := _process_function_name(t.function):
                        related_functions.append((func_name, t.location))
                elif pos is None and is_source_file(_get_file_from_non_source_trace(t)):
                    if func_name := _process_function_name(t.function):
                        related_functions.append((func_name, None))

        # deduplicate and get the function location
        related_functions, old_related_functions = [], list(set(related_functions))
        for func_name, file_loc in old_related_functions:
            if func_name.startswith("LLVMFuzzerTestOneInput"):
                # omit the fuzzer function
                continue
            if func_loc := self._get_function_loc(func_name, file_loc):
                related_functions.append((func_name, file_loc, func_loc))

        return related_functions

    def _get_related_api_functions(
        self, related_functions: list[tuple[str, str, str]]
    ) -> FunctionSet:
        """
        Filter the related functions and get the API functions.

        :param related_functions: The related functions
        :return: The related API functions
        """
        return FunctionSet(
            [
                func
                for _, _, func_loc in related_functions
                if (func := self.api_collection.get_by_location(func_loc))
            ],
            increment_id=False,
        )

    def _collect_library_code(
        self, related_functions: list[tuple[str, str, str]]
    ) -> dict[str, str]:
        """
        Collect the library code of the related functions.

        :param related_functions: The related functions
        :return: The related library code, as a dict of (function name, function code)
        """

        def _slice_whole_function(
            func_impl_start_pos: FilePos, func_impl_end_pos: FilePos
        ) -> str:
            """
            Slice the whole function implementation.

            :param func_impl_start_pos: The start position of the function implementation
            :param func_impl_end_pos: The end position of the function implementation
            :return: The function code
            """
            return func_impl_start_pos.get_content_till_pos(func_impl_end_pos)

        def _slice_lines_around(
            func_impl_start_pos: FilePos,
            func_impl_end_pos: FilePos,
            reference_poses: list[FilePos],
            lines_to_slice: int,
        ) -> str:
            """
            Slice the lines around the reference positions.

            :param func_impl_start_pos: The start position of the function implementation
            :param func_impl_end_pos: The end position of the function implementation
            :param reference_poses: The reference positions
            :param lines_to_slice: The number of lines to slice around the reference positions
            :return: The function code
            """
            reference_poses = sorted(reference_poses, key=lambda x: x.line)
            slice_ranges = []
            for pos in reference_poses:
                # get the left of the reference pos
                left = pos.copy()
                try:
                    left.line -= int(lines_to_slice / 2)
                except:
                    # may out of file
                    left = func_impl_start_pos
                else:
                    left.set_to_start_of_line()
                    if left < func_impl_start_pos:
                        left = func_impl_start_pos

                # get the right of the reference pos
                right = pos.copy()
                try:
                    right.line += int(lines_to_slice / 2)
                except:
                    # may out of file
                    right = func_impl_end_pos
                else:
                    right.set_to_end_of_line()
                    if right > func_impl_end_pos:
                        right = func_impl_end_pos

                if not slice_ranges:
                    # first range
                    slice_ranges.append((left, right))
                    continue

                # check whether the range is overlapped with last range
                last_left, last_right = slice_ranges[-1]
                if left <= last_right:
                    # overlapped
                    slice_ranges[-1] = (last_left, right)
                else:
                    # not overlapped
                    slice_ranges.append((left, right))

            # slice the code
            code = ""
            for left, right in slice_ranges:
                if left != func_impl_start_pos:
                    code += "// some code omitted...\n"
                code += left.get_content_till_pos(right)
                code += "\n"
            if slice_ranges[-1][1] != func_impl_end_pos:
                code += "// some code omitted...\n"

            return code

        # XXX There may be cases like:
        # 1. Multiple func_loc with the same func_name, i.e. overloads. We need to
        #    distinguish them with func_name@func_loc.
        # 2. Multiple file_loc in the same func_loc, i.e. recursion in backtrace. We
        #    need to handle them all at once.
        #
        # We firstly categorize the related functions by func_name, then by func_loc.
        categorized_functions = {}
        for func_name, file_loc, func_loc in related_functions:
            categorized_functions.setdefault(func_name, {}).setdefault(
                func_loc, []
            ).append(file_loc)

        # Then we collect the library code
        library_code: dict[str, str] = {}
        for func_name, func_locs in categorized_functions.items():
            for func_loc, file_locs in func_locs.items():
                # retrieve from meta
                func_obj: FunctionInfo = self.info_repo.get_info(func_loc, FunctionInfo)
                func_loc_pos = FilePos.from_location_line(func_loc)
                func_impl_start_pos, func_impl_end_pos = func_obj.impl_range
                func_impl_end_pos += 1  # include the last '}'

                # set distinguished func name
                if len(func_locs) == 1:
                    distinguished_func_name = func_name
                else:
                    distinguished_func_name = (
                        f"{func_name}@{func_loc_pos.file.name}:{func_loc_pos.line}"
                    )

                # If the related function is short, say less than 30 lines, we can directly use the function code
                # Otherwise, we slice 15 lines before and after the file location in the backtrace
                if (
                    func_impl_end_pos.line - func_impl_start_pos.line
                    <= self.PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD
                ):
                    library_code[distinguished_func_name] = _slice_whole_function(
                        func_impl_start_pos, func_impl_end_pos
                    )
                else:
                    # get reference positions
                    reference_poses = []
                    for file_loc in file_locs:
                        if file_loc is not None:
                            reference_poses.append(FilePos.from_location_line(file_loc))
                    if not reference_poses:
                        logger.warning(
                            f"Function {distinguished_func_name} implementation is too long, without file "
                            "location in the backtrace PromeFuzz cannot slice the code, skippping. "
                            "Please compile the library with debug info!"
                        )
                        continue
                    library_code[distinguished_func_name] = _slice_lines_around(
                        func_impl_start_pos,
                        func_impl_end_pos,
                        reference_poses,
                        self.PROVIDE_WHOLE_FUNCTION_IMPLEMENTATION_THRESHOLD,
                    )

        return library_code

    def _collect_data_defs(self, related_api_functions: FunctionSet) -> str:
        """
        Collect the data definitions of the related API functions.

        :param related_api_functions: The related API functions
        :return: The related data definitions
        """
        # Use collector to collect the data definitions
        result = self.info_collector.collect(related_api_functions)
        return result.data_definitions
