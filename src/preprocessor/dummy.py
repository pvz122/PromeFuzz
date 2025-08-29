"""
Dummy test to check whether the driver of a function can compile
"""

from abc import abstractmethod, ABC
from loguru import logger
from pathlib import Path
import shutil
from concurrent.futures import ThreadPoolExecutor

from src import vars as global_vars
from .meta import Meta
from .api import APIFunction, APICollection
from src.generator.driver import FuzzDriver


class DummyTester:
    """
    Run dummy driver tests for API functions
    """

    # some already known build errors
    KNOWN_TRUE_POSITIVES = {
        "is a protected member of": "this function is protected and cannot be called",
        # "error: no matching member function for call to": "the function is not a member of the class",
    }
    KNOWN_FALSE_POSITIVES = {
        "error: called object type 'int' is not a function or function pointer": "the template requires a function pointer",
    }

    def __init__(
        self, meta: Meta, api_collection: APICollection, saving_dir: Path = None
    ):
        """
        Initialize the dummy tester

        :param meta: The AST meta information
        :param api_collection: The API functions
        """
        self.meta = meta
        self.funcs = api_collection
        if global_vars.library_language == global_vars.SupportedLanguages.C:
            self.generator = CDummyGenerator(meta)
        elif global_vars.library_language == global_vars.SupportedLanguages.CPP:
            self.generator = CppDummyGenerator(meta)
        if saving_dir:
            self.saving_dir = saving_dir
            shutil.rmtree(self.saving_dir, ignore_errors=True)
            self.saving_dir.mkdir(parents=True, exist_ok=True)

    def run_once(self, target_function: APIFunction) -> APIFunction | None:
        """
        Run the dummy tests for one API function

        :param target_function: The target api function
        :return: None if the function passed the dummy test, or the function if it failed
        """
        logger.debug(f"Running dummy test for function {target_function.name}")

        # generate dummy fuzz driver
        dummy_driver = self.generator.generate(target_function)
        if not dummy_driver:
            return target_function

        # save the dummy fuzz driver for debugging
        if hasattr(self, "saving_dir"):
            suffix = (
                ".cpp"
                if global_vars.library_language == global_vars.SupportedLanguages.CPP
                else ".c"
            )
            dummy_driver.save(
                self.saving_dir,
                f"dummy_driver_{dummy_driver.id}{suffix}",
                save_build_script=True,
            )

        # run the dummy fuzz driver
        success, msg = dummy_driver.build(extra_build_args=["-w"])
        if success:
            logger.debug(f"Function {target_function.name} dummy test passed")
            return None
        else:
            # check known false positives
            for error_msg, reason in self.KNOWN_FALSE_POSITIVES.items():
                if error_msg in msg:
                    logger.debug(
                        f"Function {target_function.name} dummy test failed, but it is a known false positive: {reason}"
                    )
                    return None
            # check known true positives
            for error_msg, reason in self.KNOWN_TRUE_POSITIVES.items():
                if error_msg in msg:
                    logger.info(
                        f"Function {target_function} will be filtered out: {reason}"
                    )
                    return target_function
            # unknown error
            logger.warning(
                f"Failed to build the dummy fuzz driver {dummy_driver.id} for function {target_function.name}, this function will be filtered out. Build output: \n{msg}"
            )
            return target_function

    def run(self, pool_size: int):
        """
        Run the dummy tests for all API functions

        :param pool_size: The number of processes in the pool
        """
        if pool_size > 1:
            pool = ThreadPoolExecutor(pool_size)
            results = pool.map(self.run_once, self.funcs.safe_iter)
        else:
            # single thread, for debugging
            results = map(self.run_once, self.funcs.safe_iter)

        failed_functions = [result for result in results if result]
        logger.debug(f"Dummy tests finished, {len(failed_functions)} functions failed")

        # remove failed functions from the collection
        for failed_function in failed_functions:
            self.funcs.remove(failed_function)


class DummyGenerator(ABC):
    """
    Generate a dummy fuzz driver.
    Dummy fuzz driver is a program that only contains a minimal call to the target function.
    It is not used for fuzzing but for build testing and debugging.
    We can use it to validate the build args and headers, as well as the api functions extraction.
    """

    def __init__(self, meta: Meta):
        """
        Initialize the dummy generator

        :param meta: The AST meta information
        """
        self.meta = meta

    @abstractmethod
    def construct_dummy_code(self, target_function: APIFunction) -> str:
        """
        Construct a dummy fuzz driver code

        :param target_function: The target api function
        :return: The dummy fuzz driver code
        """
        ...

    def generate(
        self,
        target_function: APIFunction,
    ) -> FuzzDriver | None:
        """
        Generate a dummy fuzz driver

        :param target_function: The target api function
        :return: The dummy fuzz driver
        """
        from src.generator.scheduler import FunctionSet  # to avoid circular import

        # create a FunctionSet object
        function_set = FunctionSet([target_function])

        # generate dummy fuzz driver code
        dummy_code = self.construct_dummy_code(target_function)
        if not dummy_code:
            return None

        # create a fuzz driver object
        fuzz_driver = FuzzDriver(dummy_code, None, function_set)

        return fuzz_driver


class CDummyGenerator(DummyGenerator):
    """
    Generate a dummy fuzz driver for C library
    """

    def construct_dummy_code(self, target_function: APIFunction) -> str:
        """
        Construct a dummy fuzz driver code for C function

        :param target_function: The target function
        :return: The dummy fuzz driver code
        """
        # get param types
        func_obj = self.meta.functions_ori.get(target_function.loc, None)
        if not func_obj:
            logger.error(
                f"Function {target_function.name} not found in meta data when generating dummy code."
            )
            return ""
        param_types = list(param["realType"] for param in func_obj["param"])
        param_statements = ", ".join(f"({t})0" for t in param_types)

        # get headers
        header_names = [Path(target_function.header).name]
        header_names += global_vars.library_config["driver_headers"]
        header_names = list(set(header_names))
        header_statements = "\n".join(
            f'#include "{header_name}"' for header_name in header_names
        )

        # generate dummy fuzz driver code
        dummy_code = """// This is a dummy fuzz driver for testing the build of the target function {target_function}
#include <stdint.h>
#include <stddef.h>
{headers}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {{
    {target_function}({params});  // dummy function call
    return 0;
}}
""".format(
            target_function=target_function.name,
            headers=header_statements,
            params=param_statements,
        )

        return dummy_code


class CppDummyGenerator(DummyGenerator):
    """
    Generate a dummy fuzz driver for C++ library
    """

    def construct_dummy_code(self, target_function: APIFunction) -> str:
        """
        Construct a dummy fuzz driver code for C++ function

        :param target_function: The target api function
        :return: The dummy fuzz driver code
        """
        # C++ function calling is more complex than C
        # 1. If the function is a class member, we need to create an instance of the class
        # 2. If the class is a template class, we need to pass template arguments
        # 3. If the function is a template function, we need to pass template arguments and int type as function params
        # 4. If the function param is a composite type, we need to create an instance of the type
        # 5. If the function param is a function pointer, we pass nullptr

        # FIXME: This generator still does not work properly for all cases. e.g., some template functions can only be
        # called with specific template arguments, and some composite types need to be initialized with specific values.
        # We may improve this generator in the future. But for now, we just turn this feature off.

        # some variables
        CPP_DUMMY_TEMPLATE = """// This is a dummy fuzz driver for testing the build of the target function {target_function}
#include <iostream>
#include <cstdint>
#include <cstddef>
{headers}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {{
    {instance_init}
    {function_call}{template_params}({param_passing});  // dummy function call
    return 0;
}}
"""
        instance_init = []
        instance_init_count = 0

        def create_instance(type_name: str, class_name: str) -> str:
            """
            Create an instance of a class type

            :param type_name: The type name
            :param class_name: The original class name
            :return: The instance variable name
            """
            nonlocal instance_init_count
            nonlocal instance_init
            instance_init_count += 1

            # lookup class_name in meta
            class_objs = self.meta.composites.get(class_name, None)
            if not class_objs:
                # if not found, just handle it as non-template class
                template_param_count = 0
            else:
                # only consider the first class obj
                template_param_count = next(iter(class_objs.values()))[
                    "templateParamNum"
                ]

            if template_param_count:
                # if it is a template class, pass int type as template arguments
                # FIXME: does this replacement work for all cases?
                t = type_name.replace(
                    class_name,
                    f"{class_name}<{', '.join('int' for _ in range(template_param_count))}>",
                )
            else:
                t = type_name
            instance_init.append(f"{t}* instance_{instance_init_count} = nullptr;")
            return f"instance_{instance_init_count}"

        # get func obj
        func_name = target_function.name
        func_obj = self.meta.functions_ori.get(target_function.loc, None)
        if not func_obj:
            logger.error(
                f"Function {target_function.name} not found in meta data when generating dummy code."
            )
            return ""

        # get headers
        header_names = [Path(target_function.header).name]
        header_names += global_vars.library_config["driver_headers"]
        header_names = list(set(header_names))
        header_statements = "\n".join(
            f'#include "{header_name}"' for header_name in header_names
        )

        # handle function as a class member
        if heldby_class := func_obj["heldbyClass"]:
            # this is a class method
            heldby_class_instance = create_instance(heldby_class, heldby_class)
            function_calling = f"{heldby_class_instance}->{func_name.split('::')[-1]}"
        else:
            function_calling = func_name

        # handle all params
        param_passing = []
        for param in func_obj["param"]:
            if (
                param["isBuiltin"] and "std::" not in param["realType"]
            ):  # std:: should be handled as composite type
                # if it is a built-in type, just pass 0
                param_passing.append(f"({param['realType']})0")
            elif param["isFuncPointer"]:
                # if it is a function pointer, pass nullptr
                param_passing.append("nullptr")
            elif "type-parameter" in param["realType"]:
                # if it is a template type, pass an arbitrary type
                param_passing.append("0")
            else:
                # if it is a composite type, create an instance
                param_type = (
                    param["realType"].replace("const", "").replace("&", "").strip()
                )  # remove const and reference
                param_instance = create_instance(param_type, param["baseType"])
                param_passing.append(f"*{param_instance}")

        # handle template function params
        template_params = ""
        if param_num := func_obj["templateParamNum"]:
            template_params = f"<{', '.join('int' for _ in range(param_num))}>"

        # generate dummy fuzz driver code
        dummy_code = CPP_DUMMY_TEMPLATE.format(
            target_function=target_function.name,
            headers=header_statements,
            instance_init="\n    ".join(instance_init),
            template_params=template_params,
            function_call=function_calling,
            param_passing=", ".join(param_passing),
        )

        return dummy_code
