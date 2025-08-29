"""
Extract information repository from the Meta, which is a dependency graph of language objects.

Design:
The idea here is to retrieve all needed information at preprocess stage, while still offering some flexibilities at generation stage.
Hence, the `info` module is designed as a directed graph which stores all used objects and their reference relationships.
These objects include functions, composite types, classes, typedefs, etc.
At preprocess stage, we create all the objects and build the graph.
Later at generation stage, we can traverse the graph to collect all the needed information.
"""

from abc import ABC
from loguru import logger
import pickle
import json
from pathlib import Path
from functools import cache
from random import choice

import src.vars as global_vars
from src.utils import filter_typename, deduplicate_list, FilePos
from .meta import Meta
from .api import APICollection
from .definition import DefinitionReader


class Info(ABC):
    """
    Abstract class to store the information.
    """

    def __init__(self):
        self.name: str = ""
        self.location: str = ""

    meta: "Meta" = None
    repository: "InfoRepository" = None

    @classmethod
    def from_name_and_location_as_empty(cls, name: str, location: str):
        """
        Create an empty information object with name and location.

        :param name: The name string.
        :param location: The location string.
        :return: The information object.
        """
        info = cls()
        info.name = name
        info.location = location
        # To avoid infinite recursion, we need to create an empty object and add it to the repository first
        # Afterwards we'll modify the object
        cls.repository.add_info(info)
        return info

    @property
    def ref_info_iter(self):
        """
        Iterate the referred information objects in this information object.
        """
        for prop in self.__dict__.values():
            if isinstance(prop, Info):
                yield prop
            elif isinstance(prop, list):
                for item in prop:
                    if isinstance(item, Info):
                        yield item

    @property
    def ref_info_iter_name_unique(self):
        """
        Iterate the referred information objects in this information object.
        Objects with the same name will be randomly selected once.
        """
        for prop in self.__dict__.values():
            if isinstance(prop, Info):
                yield prop
            elif isinstance(prop, list):
                # organize the items by name
                items_by_name = {}
                for item in prop:
                    if isinstance(item, Info):
                        items_by_name.setdefault(item.name, []).append(item)
                # randomly select one item for each name
                for items in items_by_name.values():
                    yield choice(items)

    @staticmethod
    def parse_c_type(
        c_type: dict,
    ) -> tuple[list["CCompositeInfo"], list["CTypedefInfo"]]:
        """
        Parse the C type. Get its used composite and typedef info.

        :param c_type: The C type dict.
        :return: (used_composites, used_typedefs)
        """
        used_composites = []
        used_typedefs = []

        if c_type["isFuncPointer"]:
            # FIXME: we do not process function pointer yet
            return used_composites, used_typedefs

        named_type = filter_typename(c_type["type"])
        base_type = c_type["baseType"]
        if not c_type["isBuiltin"]:
            # This is a composite type, we need to find the composite info
            used_composites.extend(CCompositeInfo.from_name(base_type))

        # for all named types, we need to find the typedef info
        used_typedefs.extend(CTypedefInfo.from_name(named_type, no_warning=True))
        used_typedefs.extend(CTypedefInfo.from_name(c_type["type"], no_warning=True))

        return used_composites, used_typedefs

    @staticmethod
    def parse_c_type_list(
        type_list: list[dict],
    ) -> tuple[list["CCompositeInfo"], list["CTypedefInfo"]]:
        """
        Parse the C types in the type list. Get their used composite and typedef info.

        :param type_list: The type list.
        :return: (used_composites, used_typedefs)
        """
        used_composites = []
        used_typedefs = []

        for used_type in type_list:
            new_composites, new_typedefs = Info.parse_c_type(used_type)
            used_composites.extend(new_composites)
            used_typedefs.extend(new_typedefs)

        # deduplicate the list
        used_composites = deduplicate_list(used_composites)
        used_typedefs = deduplicate_list(used_typedefs)

        return used_composites, used_typedefs

    @staticmethod
    def parse_cpp_type(
        cpp_type: dict,
    ) -> tuple[list["CppCompositeInfo"], list["ClassInfo"], list["CppTypedefInfo"]]:
        """
        Parse the C++ type. Get its used composite, class and typedef

        :param cpp_type: The C++ type dict.
        :return: (used_composites, used_classes, used_typedefs)
        """
        used_composites = []
        used_classes = []
        used_typedefs = []

        if cpp_type["isFuncPointer"]:
            return used_composites, used_classes, used_typedefs

        if "type-parameter" in cpp_type["realType"]:
            # This is a template type, we skip it
            return used_composites, used_classes, used_typedefs

        if cpp_type["isTemplateType"]:
            # This is a template type, we need to parse the disassembled template types recursively
            for tmpl_type in cpp_type["disassembledTemplateTypes"]:
                new_composites, new_classes, new_typedefs = Info.parse_cpp_type(
                    tmpl_type
                )
                used_composites.extend(new_composites)
                used_classes.extend(new_classes)
                used_typedefs.extend(new_typedefs)
        else:
            named_type = filter_typename(cpp_type["type"])
            base_type = cpp_type["baseType"]
            base_type = (
                base_type[base_type.find(" ") + 1 :] if " " in base_type else base_type
            )
            # It's like:
            # "baseType": "struct json_object"
            # This is fine for C, but for C++, we need to remove the "struct" keyword
            real_type = cpp_type["realType"]
            # Sometimes the realType is the composite name...
            # For example:
            # "baseType": "enum jsonxx::Value::(unnamed at xxx)"
            # "realType": "jsonxx::Value::(unnamed enum at xxx)"

            # Helper functions
            find_flag = False

            def in_composite(type_name: str) -> bool:
                if (
                    type_name in Info.meta.composites.keys()
                    or type_name in Info.meta.enums.keys()
                ):
                    nonlocal find_flag
                    find_flag = True
                    return True
                return False

            def in_class(type_name: str) -> bool:
                if type_name in Info.meta.classes.keys():
                    nonlocal find_flag
                    find_flag = True
                    return True
                return False

            if not cpp_type["isBuiltin"]:
                # This is a user-defined type, get the composite and class info
                if in_composite(base_type):
                    used_composites.extend(CppCompositeInfo.from_name(base_type))
                if in_class(base_type):
                    used_classes.extend(ClassInfo.from_name(base_type))
                if in_composite(real_type):
                    used_composites.extend(CppCompositeInfo.from_name(real_type))
                if in_class(real_type):
                    used_classes.extend(ClassInfo.from_name(real_type))

                if not find_flag:
                    logger.warning(f"Type {base_type} is not found in the meta data.")

            used_typedefs.extend(CppTypedefInfo.from_name(named_type, no_warning=True))
            used_typedefs.extend(
                CppTypedefInfo.from_name(cpp_type["type"], no_warning=True)
            )

        return used_composites, used_classes, used_typedefs

    def parse_cpp_type_list(
        type_list: list[dict],
    ) -> tuple[list["CppCompositeInfo"], list["ClassInfo"], list["CppTypedefInfo"]]:
        """
        Parse the C++ types in the type list. Get their used composite, class and typedef info.

        :param type_list: The type list.
        :return: (used_composites, used_classes, used_typedefs)
        """
        used_composites = []
        used_classes = []
        used_typedefs = []

        for used_type in type_list:
            new_composites, new_classes, new_typedefs = Info.parse_cpp_type(used_type)
            used_composites.extend(new_composites)
            used_classes.extend(new_classes)
            used_typedefs.extend(new_typedefs)

        # deduplicate the list
        used_composites = deduplicate_list(used_composites)
        used_classes = deduplicate_list(used_classes)
        used_typedefs = deduplicate_list(used_typedefs)

        return used_composites, used_classes, used_typedefs

    def __eq__(self, value) -> bool:
        return type(self) == type(value) and self.location == value.location

    def __hash__(self):
        return hash(type(self)) + hash(self.location)


class FunctionInfo(Info):
    def __init__(self):
        self.signature: str = ""
        self.used_composites = []
        self.used_typedefs = []
        self.impl_range: tuple[FilePos, FilePos] = (None, None)


class CFunctionInfo(FunctionInfo):
    """
    Class to store the information of a C function.
    """

    # A C function may need below information:
    # 1. Name of the function
    # 2. Location of the function, as a identifier
    # 3. Function signature
    # 4. Used composite info
    # 5. Used typedef info
    # 6. Position range of the implementation

    def __init__(self):
        self.signature: str = ""
        self.used_composites: list["CCompositeInfo"] = []
        self.used_typedefs: list["CTypedefInfo"] = []
        self.impl_range: tuple[FilePos, FilePos] = (None, None)

    @classmethod
    def from_location(cls, location: str) -> "CFunctionInfo":
        """
        Create the CFunctionInfo object of a function location.

        :param location: The function location string.
        :return: A CFunctionInfo object.
        """
        # check if the function info is already in the repository
        if (func_info := cls.repository.get_info(location, cls)) is not None:
            return func_info

        func_obj = cls.meta.functions_ori.get(location, None)
        if func_obj is None:
            logger.warning(
                f"Function location {location} is not found in the meta data."
            )
            return None

        func_info = cls.from_name_and_location_as_empty(func_obj["name"], location)

        # get signature
        signature_locrange = (
            func_obj["declLocRange"]
            if func_obj["declLocRange"]
            else func_obj["locRange"]
        )
        _, _, func_info.signature = DefinitionReader.read_function_signature(
            signature_locrange
        )

        # get implementation
        try:
            func_info.impl_range = DefinitionReader.parse_locrange(func_obj["locRange"])
        except ValueError as e:
            logger.error(
                f"Error parsing location range for function {func_obj["name"]}, its locRange is {func_obj["locRange"]}, error: {e}"
            )

        # get used types
        used_type_objs: list = func_obj["param"]
        used_type_objs.append(func_obj["return"])

        func_info.used_composites, func_info.used_typedefs = cls.parse_c_type_list(
            used_type_objs
        )

        return func_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CFunctionInfo"]:
        """
        Create all CFunctionInfo objects of function name.

        :param name: The function name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CFunctionInfo objects.
        """
        # retrieve all the function locations of this name
        func_locs = cls.meta.functions.get(name, {}).keys()
        if len(func_locs) == 0 and not no_warning:
            logger.warning(f"Function name {name} is not found in the meta data.")
        func_infos = []

        for func_loc in func_locs:
            func_info = cls.from_location(func_loc)
            if func_info is not None:
                func_infos.append(func_info)

        return func_infos


class CppFunctionInfo(FunctionInfo):
    """
    Class to store the information of a C++ function.
    """

    # A C++ function may need below information:
    # 1. Name of the function
    # 2. Location of the function, as a identifier
    # 3. Function signature
    # 4. Used composite info
    # 5. Used typedef info
    # 6. Held-by namespace and class
    # 7. Related class info
    # 8. Position range of the implementation

    def __init__(self):
        self.signature: str = ""
        self.used_composites: list["CppCompositeInfo"] = []
        self.used_typedefs: list["CppTypedefInfo"] = []
        self.heldby_namespace: str = ""
        self.heldby_class: str = ""
        self.related_class: list["ClassInfo"] = []
        self.impl_range: tuple[FilePos, FilePos] = (None, None)

    @classmethod
    def from_location(cls, location: str) -> "CppFunctionInfo":
        """
        Create the CppFunctionInfo object of a function location.

        :param location: The function location string.
        :return: A CppFunctionInfo object.
        """
        # check if the function info is already in the repository
        if (func_info := cls.repository.get_info(location, cls)) is not None:
            return func_info

        func_obj = cls.meta.functions_ori.get(location, None)
        if func_obj is None:
            func_obj = cls.meta.functions_decl.get(location, None)
        if func_obj is None:
            logger.warning(
                f"Function location {location} is not found in the meta data."
            )
            return None

        func_info = cls.from_name_and_location_as_empty(func_obj["name"], location)

        # get signature
        signature_locrange = (
            func_obj["declLocRange"]
            if func_obj["declLocRange"]
            else func_obj["locRange"]
        )
        _, _, func_info.signature = DefinitionReader.read_function_signature(
            signature_locrange, is_template=(func_obj["templateParamNum"] != 0)
        )

        # get implementation
        try:
            func_info.impl_range = DefinitionReader.parse_locrange(func_obj["locRange"])
        except ValueError as e:
            logger.error(
                f"Error parsing location range for function {func_obj["name"]}, its locRange is {func_obj["locRange"]}, error: {e}"
            )

        # get heldby namespace and class
        func_info.heldby_namespace = func_obj["heldbyNamespace"]
        func_info.heldby_class = func_obj["heldbyClass"]

        # get class info it belongs to
        if func_info.heldby_class:
            func_info.related_class.extend(ClassInfo.from_name(func_info.heldby_class))

        # get used types
        used_type_objs: list = func_obj["param"]
        used_type_objs.append(func_obj["return"])

        func_info.used_composites, used_classes, func_info.used_typedefs = (
            cls.parse_cpp_type_list(used_type_objs)
        )
        func_info.related_class.extend(used_classes)

        return func_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CppFunctionInfo"]:
        """
        Create all CppFunctionInfo objects of function name.

        :param name: The function name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CppFunctionInfo objects.
        """
        # retrieve all the function locations of this name
        func_locs = cls.meta.functions.get(name, {}).keys()
        if len(func_locs) == 0 and not no_warning:
            logger.warning(f"Function name {name} is not found in the meta data.")
        func_infos = []

        for func_loc in func_locs:
            func_info = cls.from_location(func_loc)
            if func_info is not None:
                func_infos.append(func_info)

        return func_infos


# We define ConstructorInfo as same as FunctionInfo here
# because we want to distinguish them when iterating the repository
class ConstructorInfo(CppFunctionInfo): ...


class CompositeInfo(Info): ...


class CCompositeInfo(CompositeInfo):
    """
    Class to store the information of a C composite type.
    """

    # A C composite type may need below information:
    # 1. Name of the composite type
    # 2. Location of the composite type, as a identifier
    # 3. Composite definition
    # 4. Used composite info
    # 5. Used typedef info

    def __init__(self):
        self.definition: str = ""
        self.used_composites: list["CCompositeInfo"] = []
        self.used_typedefs: list["CTypedefInfo"] = []

    @classmethod
    def from_location(cls, location: str, kind: str = "composite") -> "CCompositeInfo":
        """
        Create the CCompositeInfo object of a composite location.

        :param location: The composite location string.
        :param kind: The kind of the composite. Can be "composite" or "enum".
        :return: A CCompositeInfo object.
        """
        # check if the composite info is already in the repository
        if (composite_info := cls.repository.get_info(location, cls)) is not None:
            return composite_info

        composite_obj = None
        if kind == "composite":
            composite_obj = cls.meta.composites_ori.get(location, None)
        elif kind == "enum":
            composite_obj = cls.meta.enums_ori.get(location, None)

        if composite_obj is None:
            logger.warning(
                f"Composite location {location} is not found in the meta data."
            )
            return None

        composite_info = cls.from_name_and_location_as_empty(
            composite_obj["name"], location
        )

        # get definition
        definition_locrange = composite_obj["locRange"]
        _, _, composite_info.definition = (
            DefinitionReader.read_simple_composite_definition(definition_locrange)
        )

        if kind == "composite":
            # if it is a composite, we parse the members
            composite_info.used_composites, composite_info.used_typedefs = (
                cls.parse_c_type_list(composite_obj["members"])
            )
        else:
            # if it is an enum, its used composites and typedefs are empty
            composite_info.used_composites = []
            composite_info.used_typedefs = []

        return composite_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CCompositeInfo"]:
        """
        Create all CCompositeInfo objects of composite name.

        :param name: The composite name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CCompositeInfo objects.
        """
        # retrieve all the composite locations of this name
        composite_locs = cls.meta.composites.get(name, {}).keys()
        enum_locs = cls.meta.enums.get(name, {}).keys()

        if len(composite_locs) == 0 and len(enum_locs) == 0 and not no_warning:
            logger.warning(f"Composite name {name} is not found in the meta data.")

        composite_infos = []
        for composite_loc in composite_locs:
            composite_info = cls.from_location(composite_loc, kind="composite")
            if composite_info is not None:
                composite_infos.append(composite_info)
        for enum_loc in enum_locs:
            enum_info = cls.from_location(enum_loc, kind="enum")
            if enum_info is not None:
                composite_infos.append(enum_info)

        return composite_infos


class CppCompositeInfo(CompositeInfo):
    """
    Class to store the information of a C++ composite type.
    """

    # A C++ composite type may need below information:
    # 1. Name of the composite type
    # 2. Location of the composite type, as a identifier
    # 3. Composite definition
    # 4. Used composite info
    # 5. Used typedef info
    # 6. Held-by namespace and class
    # 7. Related class info
    # 8. Composite kind (class, struct, union, enum, unknown)

    def __init__(self):
        self.definition: str = ""
        self.used_composites: list["CppCompositeInfo"] = []
        self.used_typedefs: list["CppTypedefInfo"] = []
        self.heldby_namespace: str = ""
        self.heldby_class: str = ""
        self.related_class: list["ClassInfo"] = []
        self.kind: str = ""

    @classmethod
    def from_location(
        cls, location: str, kind: str = "composite"
    ) -> "CppCompositeInfo":
        """
        Create the CppCompositeInfo object of a composite location.

        :param location: The composite location string.
        :param kind: The kind of the composite. Can be "composite" or "enum".
        :return: A CppCompositeInfo object.
        """
        # check if the composite info is already in the repository
        if (composite_info := cls.repository.get_info(location, cls)) is not None:
            return composite_info

        composite_obj = None
        if kind == "composite":
            composite_obj = cls.meta.composites_ori.get(location, None)
        elif kind == "enum":
            composite_obj = cls.meta.enums_ori.get(location, None)

        if composite_obj is None:
            logger.warning(
                f"Composite location {location} is not found in the meta data."
            )
            return None

        if kind == "composite" and composite_obj["kind"] == "unknown":
            logger.warning(f"Composite {composite_obj['name']} is unknown, skipping.")
            return None

        composite_info = cls.from_name_and_location_as_empty(
            composite_obj["name"], location
        )

        # get kind
        composite_info.kind = composite_obj["kind"] if kind == "composite" else "enum"

        # get definition
        # if it's a class, skip it; if it's a struct, parse it through read_complex_composite_definition;
        # if it's an union/enum, parse it through read_simple_composite_definition
        definition_locrange = composite_obj["locRange"]
        if composite_info.kind == "class":
            # if the class is a template class, we need to get the definition to indicate generator for template parameters
            if composite_obj["templateParamNum"] != 0:
                composite_info.definition = (
                    f"// Class {composite_obj["name"]} is a template class, it looks like: \n"
                    + DefinitionReader.read_complex_composite_definition(
                        definition_locrange, tuple(), is_template=True
                    )[2]
                )
            else:
                composite_obj["definition"] = ""
        elif composite_info.kind == "enum" or composite_info.kind == "union":
            _, _, composite_info.definition = (
                DefinitionReader.read_simple_composite_definition(definition_locrange)
            )
        elif composite_info.kind == "unknown":
            # should not reach here
            composite_info.definition = ""
        elif composite_info.kind == "struct":
            # get the member definition locranges
            member_locranges = tuple(m["locRange"] for m in composite_obj["members"])
            if len(member_locranges) == 0:
                # if there is no member, we skip it
                composite_info.definition = ""
                logger.warning(
                    f"Composite {composite_obj['name']} has no member, skipping definition extraction."
                )
            else:
                _, _, composite_info.definition = (
                    DefinitionReader.read_complex_composite_definition(
                        definition_locrange,
                        member_locranges,
                        is_template=(composite_obj["templateParamNum"] != 0),
                    )
                )

        # get heldby namespace and class
        composite_info.heldby_namespace = composite_obj["heldbyNamespace"]
        composite_info.heldby_class = composite_obj["heldbyClass"]

        # get class info it belongs to
        if composite_info.heldby_class:
            composite_info.related_class.extend(
                ClassInfo.from_name(composite_info.heldby_class)
            )

        # get used types
        if kind == "composite":
            # if it is a composite, we parse the member types
            (
                composite_info.used_composites,
                used_classes,
                composite_info.used_typedefs,
            ) = cls.parse_cpp_type_list([m for m in composite_obj["members"]])
            composite_info.related_class.extend(used_classes)
        else:
            # if it is an enum, its used composites and typedefs are empty
            composite_info.used_composites = []
            composite_info.used_typedefs = []

        return composite_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CppCompositeInfo"]:
        """
        Create all CppCompositeInfo objects of composite name.

        :param name: The composite name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CppCompositeInfo objects.
        """
        # retrieve all the composite locations of this name
        composite_locs = cls.meta.composites.get(name, {}).keys()
        enum_locs = cls.meta.enums.get(name, {}).keys()

        if len(composite_locs) == 0 and len(enum_locs) == 0 and not no_warning:
            logger.warning(f"Composite name {name} is not found in the meta data.")

        composite_infos = []
        for composite_loc in composite_locs:
            composite_info = cls.from_location(composite_loc, kind="composite")
            if composite_info is not None:
                composite_infos.append(composite_info)
        for enum_loc in enum_locs:
            enum_info = cls.from_location(enum_loc, kind="enum")
            if enum_info is not None:
                composite_infos.append(enum_info)

        return composite_infos


class ClassInfo(Info):
    """
    Class to store the information of a C++ class.
    """

    # A C++ class may need below information:
    # 1. Name of the class
    # 2. Location of the class, as a identifier
    # 3. Constructor function info
    # 4. Held-by namespace and class
    # 5. Is abstract class
    # 6. For ABC, the derived class info

    def __init__(self):
        self.constructor: list[ConstructorInfo] = []
        self.heldby_namespace: str = ""
        self.heldby_class: str = ""
        self.is_abstract: bool = False
        self.abc_derived: list["ClassInfo"] = []

    @classmethod
    def from_location(cls, location: str) -> "ClassInfo":
        """
        Create the ClassInfo object of a class location.

        :param location: The class location string.
        :return: A ClassInfo object.
        """
        # check if the class info is already in the repository
        if (class_info := cls.repository.get_info(location, cls)) is not None:
            return class_info

        class_obj = cls.meta.classes_ori.get(location, None)
        if class_obj is None:
            logger.warning(f"Class location {location} is not found in the meta data.")
            return None

        class_info = cls.from_name_and_location_as_empty(class_obj["name"], location)

        class_info.heldby_namespace = class_obj["heldbyNamespace"]
        class_info.heldby_class = class_obj["heldbyClass"]

        # get constructor info
        for method_loc, method_obj in class_obj["methods"].items():
            if any(
                [
                    not method_obj["isConstructor"],  # this is not a constructor
                    not method_obj["isPublic"],  # this is a private constructor
                    method_obj["isVirtual"],  # this is a virtual constructor
                    (
                        (ctor_loc_range := method_obj["locRange"].split(" -> "))
                        and (ctor_loc_range[0] == ctor_loc_range[-1])
                    ),  # this is a dummy constructor, not implemented in the source code
                ]
            ):
                continue
            if ctor_info := ConstructorInfo.from_location(method_loc):
                class_info.constructor.append(ctor_info)

        # get derived class info
        if class_obj["isAbstract"]:
            class_info.is_abstract = True
            if class_obj["ABCDerives"]:
                for derived_class_loc in class_obj["ABCDerives"]:
                    if (
                        derived_class_info := ClassInfo.from_location(derived_class_loc)
                    ) is not None:
                        class_info.abc_derived.append(derived_class_info)
            else:
                logger.warning(
                    f"Abstract class {class_info.name} has no derived class."
                )

        return class_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["ClassInfo"]:
        """
        Create all ClassInfo objects of class name.

        :param name: The class name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of ClassInfo objects.
        """
        # retrieve all the class locations of this name
        class_locs = cls.meta.classes.get(name, {}).keys()
        if len(class_locs) == 0 and not no_warning:
            logger.warning(f"Class name {name} is not found in the meta data.")
        class_infos = []

        for class_loc in class_locs:
            class_info = cls.from_location(class_loc)
            if class_info is not None:
                class_infos.append(class_info)

        return class_infos


class TypedefInfo(Info): ...


class CTypedefInfo(TypedefInfo):
    """
    Class to store the information of a typedef.
    """

    # A C typedef may need below information:
    # 1. Name of the typedef
    # 2. Location of the typedef, as a identifier
    # 3. Typedef definition
    # 4. Used composite info
    # 5. Used typedef info

    def __init__(self):
        self.definition: str = ""
        self.used_composites: list["CCompositeInfo"] = []
        self.used_typedefs: list["CTypedefInfo"] = []

    @classmethod
    def from_location(cls, location: str) -> "CTypedefInfo":
        """
        Create the CTypedefInfo object of a typedef location.

        :param location: The typedef location string.
        :return: A CTypedefInfo object.
        """
        # check if the typedef info is already in the repository
        if (typedef_info := cls.repository.get_info(location, cls)) is not None:
            return typedef_info

        typedef_obj = cls.meta.typedefs_ori.get(location, None)
        if typedef_obj is None:
            logger.warning(
                f"Typedef location {location} is not found in the meta data."
            )
            return None

        typedef_info = cls.from_name_and_location_as_empty(
            typedef_obj["name"], location
        )

        # get definition
        typedef_locrange = typedef_obj["locRange"]
        _, _, typedef_info.definition = DefinitionReader.read_typedef_definition(
            typedef_locrange
        )

        # get used types
        type_list = [typedef_obj["underlyingType"]]
        typedef_info.used_composites, typedef_info.used_typedefs = (
            cls.parse_c_type_list(type_list)
        )

        return typedef_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CTypedefInfo"]:
        """
        Create all CTypedefInfo objects of typedef name.

        :param name: The typedef name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CTypedefInfo objects.
        """
        # retrieve all the typedef locations of this name
        typedef_locs = cls.meta.typedefs.get(name, {}).keys()

        if len(typedef_locs) == 0 and not no_warning:
            logger.warning(f"Typedef name {name} is not found in the meta data.")

        typedef_infos = []
        for typedef_loc in typedef_locs:
            typedef_info = cls.from_location(typedef_loc)
            if typedef_info is not None:
                typedef_infos.append(typedef_info)

        return typedef_infos


class CppTypedefInfo(TypedefInfo):
    """
    Class to store the information of a C++ typedef.
    """

    # A C++ typedef may need below information:
    # 1. Name of the typedef
    # 2. Location of the typedef, as a identifier
    # 3. Typedef definition
    # 4. Used composite info
    # 5. Used typedef info
    # 6. Held-by namespace and class
    # 7. Related class info

    def __init__(self):
        self.definition: str = ""
        self.used_composites: list["CppCompositeInfo"] = []
        self.used_typedefs: list["CppTypedefInfo"] = []
        self.heldby_namespace: str = ""
        self.heldby_class: str = ""
        self.related_class: list["ClassInfo"] = []

    @classmethod
    def from_location(cls, location: str) -> "CppTypedefInfo":
        """
        Create the CppTypedefInfo object of a typedef location.

        :param location: The typedef location string.
        :return: A CppTypedefInfo object.
        """
        # check if the typedef info is already in the repository
        if (typedef_info := cls.repository.get_info(location, cls)) is not None:
            return typedef_info

        typedef_obj = cls.meta.typedefs_ori.get(location, None)
        if typedef_obj is None:
            logger.warning(
                f"Typedef location {location} is not found in the meta data."
            )
            return None

        typedef_info = cls.from_name_and_location_as_empty(
            typedef_obj["name"], location
        )

        # get definition
        typedef_locrange = typedef_obj["locRange"]
        _, _, typedef_info.definition = DefinitionReader.read_typedef_definition(
            typedef_locrange
        )

        # get heldby namespace and class
        typedef_info.heldby_namespace = typedef_obj["heldbyNamespace"]
        typedef_info.heldby_class = typedef_obj["heldbyClass"]

        # get related class info
        if typedef_info.heldby_class:
            typedef_info.related_class.extend(
                ClassInfo.from_name(typedef_info.heldby_class)
            )

        # get used types
        typedef_info.used_composites, used_classes, typedef_info.used_typedefs = (
            cls.parse_cpp_type_list([typedef_obj["underlyingType"]])
        )

        typedef_info.related_class.extend(used_classes)

        return typedef_info

    @classmethod
    @cache
    def from_name(cls, name: str, no_warning: bool = False) -> list["CppTypedefInfo"]:
        """
        Create all CppTypedefInfo objects of typedef name.

        :param name: The typedef name string.
        :param no_warning: Whether to suppress the warning.
        :return: A list of CppTypedefInfo objects.
        """
        # retrieve all the typedef locations of this name
        typedef_locs = cls.meta.typedefs.get(name, {}).keys()

        if len(typedef_locs) == 0 and not no_warning:
            logger.warning(f"Typedef name {name} is not found in the meta data.")

        typedef_infos = []
        for typedef_loc in typedef_locs:
            typedef_info = cls.from_location(typedef_loc)
            if typedef_info is not None:
                typedef_infos.append(typedef_info)

        return typedef_infos


class InfoRepository:
    """
    Repository to store all the information.
    """

    def __init__(self, meta: Meta, api: APICollection):
        """
        Initialize the repository.

        :param meta: The meta data.
        :param api: The API functions.
        """

        self.meta = meta
        self.api = api
        Info.meta = meta
        Info.repository = self

        # reorganize the base to derived classes, in order to parse ABC constructor
        if global_vars.library_language == global_vars.SupportedLanguages.CPP:
            self.meta.reorganize_base_to_derived()

        # all the information objects are stored as location:object
        self.function_infos = {}
        self.composite_infos = {}
        self.class_infos = {}
        self.typedef_infos = {}

        # create all the information objects from api functions
        for func in api.safe_iter:
            if global_vars.library_language == global_vars.SupportedLanguages.C:
                CFunctionInfo.from_location(func.loc)
            elif global_vars.library_language == global_vars.SupportedLanguages.CPP:
                CppFunctionInfo.from_location(func.loc)

    def iter(
        self, start: list[Info], name_unique: bool = False, traverse_depth: int = -1
    ):
        """
        Iterate all the information objects from the start info objects.

        :param start: The start info objects.
        :param name_unique: Whether to use name-unique iterator,
                            which will randomly choose one unique info object from all the same name info objects.
        :param traverse_depth: The depth to traverse. -1 means infinite.
        :return: The generator of a tuple of (info, visited path).
        """

        # traverse the info objects
        # the info objects that have been visited
        visited_infos = set()
        # the traversing stack, each element is a tuple of (info, visited path)
        traversing_stack = [(info, []) for info in start]

        # do BFS traversal
        while traversing_stack:
            # pop the top info object in the stack
            cur_info, cur_visited_path = traversing_stack.pop()
            # check if it has been visited
            if cur_info in visited_infos:
                continue
            # check if the traverse depth is reached
            if len(cur_visited_path) > traverse_depth and traverse_depth != -1:
                continue
            # mark the info object as visited
            visited_infos.add(cur_info)

            # yield the info object
            yield cur_info, cur_visited_path

            # get the reference info objects
            ref_infos = (
                cur_info.ref_info_iter_name_unique
                if name_unique
                else cur_info.ref_info_iter
            )
            # push the reference info objects into the stack
            for ref_info in ref_infos:
                traversing_stack.append((ref_info, cur_visited_path + [cur_info]))

    def dump(self, path: Path):
        """
        Dump the repository to a file using pickle.

        :param path: The save path.
        """
        with open(path, "wb") as f:
            pickle.dump(self, f)

    @classmethod
    def load(cls, path: Path) -> "InfoRepository":
        """
        Load the repository from a file using pickle.

        :param path: The load path.
        :return: The repository object.
        """
        if not path.is_file():
            raise ValueError(f"The repository file is not found at {path}.")
        with open(path, "rb") as f:
            return pickle.load(f)

    def dump_json(self, json_path: Path):
        """
        Dump the repository to a json file.
        This is just for human readable, not for loading back.

        :param json_path: The json save path.
        """

        class InfoEncoder(json.JSONEncoder):
            def default(self, obj):
                if isinstance(obj, Info):
                    json_obj = {}
                    for p_name, p_value in obj.__dict__.items():
                        if isinstance(p_value, list):
                            if p_value:
                                for item in p_value:
                                    if isinstance(item, Info):
                                        # for Info list
                                        json_obj.setdefault(p_name, []).append(
                                            f"{item.name} ({item.location})"
                                        )
                                    else:
                                        json_obj.setdefault(p_name, []).append(item)
                            else:
                                json_obj[p_name] = p_value
                        elif isinstance(p_value, tuple) and all(
                            isinstance(item, FilePos) for item in p_value
                        ):
                            # for FilePos tuple
                            json_obj[p_name] = [str(pos) for pos in p_value]
                        else:
                            json_obj[p_name] = p_value
                    return json_obj
                else:
                    return super().default(obj)

        with open(json_path, "w") as f:
            json.dump(
                {
                    "function_infos": self.function_infos,
                    "composite_infos": self.composite_infos,
                    "class_infos": self.class_infos,
                    "typedef_infos": self.typedef_infos,
                },
                f,
                indent=4,
                cls=InfoEncoder,
            )

    def get_info(self, loc: str, cls) -> Info | None:
        """
        Get the information object by location and class.

        :param loc: The location.
        :param cls: The class which the information object belongs to.
        :return: The information object, None if not found.
        """
        if issubclass(cls, FunctionInfo):
            return self.function_infos.get(loc, None)
        elif issubclass(cls, CompositeInfo):
            return self.composite_infos.get(loc, None)
        elif issubclass(cls, ClassInfo):
            return self.class_infos.get(loc, None)
        elif issubclass(cls, TypedefInfo):
            return self.typedef_infos.get(loc, None)
        else:
            logger.error(f"Invalid class: {cls}")
            return None

    def get_info_by_name(self, name: str, cls) -> list[Info]:
        """
        Get the information object by name and class.

        :param name: The name.
        :param cls: The class which the information object belongs to.
        :return: The information object, None if not found.
        """
        if issubclass(cls, FunctionInfo):
            return [
                info
                for info in self.function_infos.values()
                if info.name == name and isinstance(info, cls)
            ]
        elif issubclass(cls, CompositeInfo):
            return [
                info
                for info in self.composite_infos.values()
                if info.name == name and isinstance(info, cls)
            ]
        elif issubclass(cls, ClassInfo):
            return [
                info
                for info in self.class_infos.values()
                if info.name == name and isinstance(info, cls)
            ]
        elif issubclass(cls, TypedefInfo):
            return [
                info
                for info in self.typedef_infos.values()
                if info.name == name and isinstance(info, cls)
            ]
        else:
            logger.error(f"Invalid class: {cls}")
            return []

    def add_info(self, info):
        """
        Add information object to the repository.

        :param info: The information object.
        """
        if isinstance(info, FunctionInfo):
            self.function_infos[info.location] = info
        elif isinstance(info, CompositeInfo):
            self.composite_infos[info.location] = info
        elif isinstance(info, ClassInfo):
            self.class_infos[info.location] = info
        elif isinstance(info, TypedefInfo):
            self.typedef_infos[info.location] = info
        else:
            logger.error(f"Invalid info object: {info}")
