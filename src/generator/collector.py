"""
Collect the required information for driver generation
"""

from pathlib import Path
from loguru import logger
from abc import ABC, abstractmethod
from dataclasses import dataclass

from src import vars as global_vars
from src.preprocessor.information import (
    InfoRepository,
    FunctionInfo,
    CppFunctionInfo,
    CFunctionInfo,
    CCompositeInfo,
    CTypedefInfo,
    CppCompositeInfo,
    CppTypedefInfo,
    ConstructorInfo,
    ClassInfo,
)
from src.preprocessor.consumer import OrderSet
from src.comprehender.comprehender import LibraryComprehension
from .scheduler import FunctionSet


class GenRequirements(ABC):
    """
    Class to store the required information for driver generation
    """

    @staticmethod
    def _get_headers(headers: list[str]) -> str:
        """
        Get the headers string from the headers list

        :param headers: The headers list, each element is a header file path
        """
        header_names = [Path(header).name for header in headers]
        header_names += [
            Path(header).name for header in global_vars.library_config["driver_headers"]
        ]
        header_names = list(set(header_names))

        # to pass to the LLM prompt template, we need to make it be like:
        # `header1.h`, `header2.h`, ...
        header_str = ", ".join(f"`{h}`" for h in header_names)

        return header_str


class CGenRequirements(GenRequirements):
    """
    Class to store the required information for C driver generation
    """

    def __init__(
        self,
        library_purpose: str,
        function_requirements: list["FuncRequirement"],
        type_definitions: list[str],
        typedef_definitions: list[str],
        headers: list[str],
        api_order: list[str] = None,
    ):
        """
        Initialize the C generation requirements

        :param library_purpose: The purpose of the library
        :param function_requirements: The function requirements
        :param type_definitions: The type definitions
        :param typedef_definitions: The typedef definitions
        :param headers: The headers
        :param api_order: The order of the APIs to be called, default is not specified
        """
        self.library_name = global_vars.library_name
        self.library_purpose = library_purpose
        self.target_functions = function_requirements
        self.data_definitions = (
            "\n\n".join(type_definitions) + "\n\n" + "\n".join(typedef_definitions)
        ).strip()
        self.headers = self._get_headers(headers)
        self.api_order = api_order


class CppGenRequirements(GenRequirements):
    """
    Class to store the required information for C++ driver generation
    """

    def __init__(
        self,
        library_purpose: str,
        function_requirements: list["FuncRequirement"],
        type_definitions: list["CppDefinition"],
        typedef_definitions: list["CppDefinition"],
        constructor_signatures: list["CppDefinition"],
        headers: list[str],
        api_order: list[str] = None,
    ):
        """
        Initialize the C++ generation requirements

        :param library_purpose: The purpose of the library
        :param function_requirements: The function requirements
        :param type_definitions: The type definitions
        :param typedef_definitions: The typedef definitions
        :param constructor_signatures: The constructor signatures
        :param headers: The headers
        :param api_order: The order of the APIs to be called, default is not specified
        """
        self.library_name = global_vars.library_name
        self.library_purpose = library_purpose
        self.target_functions = function_requirements
        self.data_definitions = self._collect_definitions(
            type_definitions + typedef_definitions
        ).strip()
        self.constructor_signatures = self._collect_definitions(
            constructor_signatures
        ).strip()
        self.headers = self._get_headers(headers)
        self.api_order = api_order

    def _collect_definitions(self, definitions: list["CppDefinition"]) -> str:
        """
        Collect the definitions from the list of tuples

        :param definitions: The list of definitions
        :return: The collected definitions
        """
        # We need to categorize the definitions to
        # {"namespace": {"class": ["definition"], "global": ["definition"]}, "global": ["definition"]}
        definitions_categorized = dict()
        for d in definitions:
            if d.heldby_namespace:
                definitions_categorized.setdefault(d.heldby_namespace, dict())
                if d.heldby_class:
                    definitions_categorized[d.heldby_namespace].setdefault(
                        d.heldby_class, []
                    ).append(d.content)
                else:
                    definitions_categorized[d.heldby_namespace].setdefault(
                        "global", []
                    ).append(d.content)
            else:
                definitions_categorized.setdefault("global", []).append(d.content)

        # construct the collected definitions into a string
        collected_definitions = ""
        for ns, ns_definitions in definitions_categorized.items():
            if ns_definitions:
                if ns == "global":
                    for content in ns_definitions:
                        collected_definitions += content + "\n"
                else:
                    collected_definitions += "namespace {} {{\n".format(ns)
                    for cls, cls_definitions in ns_definitions.items():
                        if cls_definitions:
                            if cls == "global":
                                for content in cls_definitions:
                                    collected_definitions += content + "\n"
                            else:
                                collected_definitions += "class {} {{\n".format(cls)
                                for content in cls_definitions:
                                    collected_definitions += content + "\n"
                                collected_definitions += "};\n"
                    collected_definitions += "}\n"

        return collected_definitions


@dataclass
class FuncRequirement:
    """
    Class to store the required information for a function
    It contains:
    - name: The name of the function
    - signature: The signature of the function
    - signature_count: The overload count of the function
    - heldby_class: The class that holds the function
    - usage: The usage of the function
    """

    name: str
    """
    Name of the function
    """

    signature: str
    """
    Signature of the function
    """

    signature_count: int
    """
    The overload count of the function
    """

    heldby_class: str = ""
    """
    The class that holds the function
    """

    usage: str = ""
    """
    Usage of the function
    """

    @classmethod
    def from_empty(cls, name: str):
        """
        Create a FuncRequirement object with only the name

        :param name: The name of the function
        :return: The created FuncRequirement object
        """
        return cls(
            name=name,
            signature="",
            signature_count=0,
        )


class InfoCollector(ABC):
    """
    Class to collect the required information for driver generation
    """

    # the depth to traverse the references
    COLLECT_DEPTH = 3
    # whether to collect only one info in the infos with the same name, otherwise collect all
    COLLECT_ONE_IN_SAME_NAMES = True

    def __init__(self, info_repo: InfoRepository, comprehension: LibraryComprehension):
        """
        Initialize the info collector

        :param info_repo: The info repository
        :param comprehension: The library comprehension
        """
        self.info_repo = info_repo
        self.comprehension = comprehension

    def collect_func(self, function_set: FunctionSet) -> list[FuncRequirement]:
        """
        Collect function requirements

        :param function_set: The target function set
        :return: The collected function requirements
        """
        results = []

        for func_name in function_set.function_names:
            func_req = FuncRequirement.from_empty(func_name)

            # get the function comprehension
            func_req.usage = self.comprehension.functions.get(func_name, "")

            # get signatures
            func_locs = function_set.get_locations_by_name(func_name)
            for loc in func_locs:
                func_info: FunctionInfo = self.info_repo.get_info(loc, FunctionInfo)
                if not func_info:
                    logger.error(f"Can not find the function info for {loc}")
                    continue
                func_req.signature_count += 1
                func_req.signature += func_info.signature + "\n"
                if (
                    isinstance(func_info, CppFunctionInfo)
                    and func_req.heldby_class == ""
                ):
                    func_req.heldby_class = func_info.heldby_class
            func_req.signature = func_req.signature.strip()
            results.append(func_req)

        return results

    @abstractmethod
    def collect_info(self, function_set: FunctionSet): ...

    @abstractmethod
    def collect(self, target_functions: FunctionSet | OrderSet) -> GenRequirements: ...


class CInfoCollector(InfoCollector):
    """
    Class to collect C library information
    """

    def collect_info(self, function_set: FunctionSet) -> tuple[list[str], list[str]]:
        """
        Collect from info repository

        :param function_set: The target function set
        :return: The collected type definitions and typedef definitions
        """
        # get target function infos
        function_infos = list()
        for loc in function_set.function_locations:
            if func_info := self.info_repo.get_info(loc, CppFunctionInfo):
                function_infos.append(func_info)
            else:
                logger.error(f"Can not find the function info for {loc}")

        # required information
        type_definitions = []
        typedef_definitions = []

        # iterate through the infos to get all needed information
        for info, _ in self.info_repo.iter(
            function_infos,
            name_unique=self.COLLECT_ONE_IN_SAME_NAMES,
            traverse_depth=self.COLLECT_DEPTH,
        ):
            if isinstance(info, CFunctionInfo):
                # this is a function info, skip it
                # all api functions info will be collected in the function_requirements
                pass
            elif isinstance(info, CCompositeInfo):
                # this is a composite info, add its definition to the type_definitions
                if info.definition:
                    type_definitions.append(info.definition)
            elif isinstance(info, CTypedefInfo):
                # this is a typedef info, add its definition to the typedef_definitions
                if info.definition:
                    typedef_definitions.append(info.definition)

        return type_definitions, typedef_definitions

    def collect(self, target_functions: FunctionSet | OrderSet) -> CGenRequirements:
        """
        Collect the specific information for C driver generation

        :param target_functions: The target function set or order set
        (if the target functions are provided in a specific order)
        :return: The generation requirements object
        """
        if isinstance(target_functions, FunctionSet):
            function_set = target_functions
            api_order = None
        elif isinstance(target_functions, OrderSet):
            function_set = target_functions.as_function_set
            api_order = [f.name for f in target_functions.order_list]

        # collect function requirements
        function_requirements = self.collect_func(function_set)

        # collect type and typedef definitions
        type_definitions, typedef_definitions = self.collect_info(function_set)

        # create the generation requirements
        gen_requirements = CGenRequirements(
            library_purpose=self.comprehension.purpose,
            function_requirements=function_requirements,
            type_definitions=type_definitions,
            typedef_definitions=typedef_definitions,
            headers=function_set.header_paths,
            api_order=api_order,
        )

        return gen_requirements


@dataclass
class CppDefinition:
    """
    Class to store the definition information for C++ language elements
    """

    content: str
    """
    The definition content
    """

    heldby_namespace: str
    """
    The namespace that holds the definition
    """

    heldby_class: str
    """
    The class that holds the definition
    """


class CppInfoCollector(InfoCollector):
    """
    Class to collect C++ library information
    """

    def collect_info(
        self, function_set: FunctionSet
    ) -> tuple[list[CppDefinition], list[CppDefinition], list[CppDefinition]]:
        """
        Collect from info repository

        :param function_set: The target function set
        :return: The collected type definitions, typedef definitions and constructor signatures
        """

        # get target function infos
        function_infos = list()
        for loc in function_set.function_locations:
            if func_info := self.info_repo.get_info(loc, CppFunctionInfo):
                function_infos.append(func_info)
            else:
                logger.error(f"Can not find the function info for {loc}")

        # required information
        type_definitions = []
        typedef_definitions = []
        constructor_signatures = []

        # for debug
        visited_path_str = lambda visited_path: " -> ".join(
            [visited_info.name for visited_info in visited_path]
        )

        # iterate through the infos to get all needed information
        for cur_info, cur_visited_path in self.info_repo.iter(
            function_infos,
            name_unique=self.COLLECT_ONE_IN_SAME_NAMES,
            traverse_depth=self.COLLECT_DEPTH,
        ):
            # deal with the current info
            if isinstance(cur_info, ConstructorInfo):
                # this is a constructor info, we want to know which class it purpose to construct
                # the visited path is like:
                # ... -> abstract class 1 -> abstract class 2 -> real class -> constructor
                # or just:
                # ... -> real class -> constructor
                # so we traverse backward to find the last class info
                purposed_class_info = None
                for visited_info in reversed(cur_visited_path):
                    if isinstance(visited_info, ClassInfo):
                        purposed_class_info = visited_info
                        break
                if purposed_class_info is not None:
                    # we've found the purposed class info, if it's a real class, simply add its constructor signature
                    # if it's an abstract class, add comment to the constructor_signatures
                    signature = cur_info.signature
                    if signature:
                        if purposed_class_info.is_abstract:
                            signature = (
                                f"// {purposed_class_info.name} is an abstract class, and {cur_info.heldby_class} is derived from it\n"
                                + signature
                            )
                        constructor_signatures.append(
                            CppDefinition(
                                signature,
                                cur_info.heldby_namespace,
                                cur_info.heldby_class,
                            )
                        )
                        # logger.debug(
                        #     f"Add signature of {cur_info.name} to the constructor_signatures, its visited path is {visited_path_str(cur_visited_path)}"
                        # )
                else:
                    logger.warning(
                        f"Can not find the purposed class info for the constructor {cur_info.name}"
                    )
            elif isinstance(cur_info, CppCompositeInfo):
                # this is a composite info, if it has a definition, add it to the type_definitions
                if cur_info.definition:
                    type_definitions.append(
                        CppDefinition(
                            cur_info.definition,
                            cur_info.heldby_namespace,
                            cur_info.heldby_class,
                        )
                    )
                    # logger.debug(
                    #     f"Add definition of {cur_info.name} to the type_definitions, its visited path is {visited_path_str(cur_visited_path)}"
                    # )
            elif isinstance(cur_info, CppTypedefInfo):
                # this is a typedef info, add its definition to the typedef_definitions
                if cur_info.definition:
                    typedef_definitions.append(
                        CppDefinition(
                            cur_info.definition,
                            cur_info.heldby_namespace,
                            cur_info.heldby_class,
                        )
                    )
                    # logger.debug(
                    #     f"Add definition of {cur_info.name} to the typedef_definitions, its visited path is {visited_path_str(cur_visited_path)}"
                    # )
            elif isinstance(cur_info, CppFunctionInfo):
                # this is a function info, skip it
                # all api functions info will be collected in the function_requirements
                pass
            elif isinstance(cur_info, ClassInfo):
                # this is a class info, do nothing
                # we only care about the constructors
                pass

        return type_definitions, typedef_definitions, constructor_signatures

    def collect(self, target_functions: FunctionSet | OrderSet) -> CppGenRequirements:
        """
        Collect the specific information for C++ driver generation

        :param target_functions: The target function set or order set
        (if the target functions are provided in a specific order)
        :return: The generation requirements object
        """
        if isinstance(target_functions, FunctionSet):
            function_set = target_functions
            api_order = None
        elif isinstance(target_functions, OrderSet):
            function_set = target_functions.as_function_set
            api_order = [f.name for f in target_functions.order_list]

        # collect function requirements
        function_requirements = self.collect_func(function_set)

        # collect type and typedef definitions
        type_definitions, typedef_definitions, constructor_signatures = (
            self.collect_info(function_set)
        )

        # create the generation requirements
        gen_requirements = CppGenRequirements(
            library_purpose=self.comprehension.purpose,
            function_requirements=function_requirements,
            type_definitions=type_definitions,
            typedef_definitions=typedef_definitions,
            constructor_signatures=constructor_signatures,
            headers=function_set.header_paths,
            api_order=api_order,
        )

        return gen_requirements
