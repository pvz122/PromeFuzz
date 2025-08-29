import json
import tree_sitter_rust as ts_rust

from abc import ABC, abstractmethod
from pathlib import Path
from loguru import logger
from tree_sitter import Language, Parser, Node

RUST_LANGUAGE = Language(ts_rust.language())


class BaseParser(ABC):
    def __init__(self, path_file: Path, language):
        parser = Parser(language)
        rust_code = path_file.read_text()
        tree = parser.parse(rust_code.encode())
        self.root_node = tree.root_node
        self.filename = str(path_file)

        # Middle res
        self.depth = 0

        # For output
        self.classes = dict()
        self.functions = dict()
        self.composites = dict()
        self.enums = dict()
        self.typedefs = dict()

    def parse(self):
        self._traverse(self.root_node)

    @abstractmethod
    def _traverse(self, node: Node):
        pass

    def _get_name(self, node) -> str:
        """Extract the name from the node."""
        for child in node.children:
            if child.type == "identifier":
                return child.text.decode()
        return ""

    def _get_start(self, node) -> str:
        start_byte, start_point = node.start_byte, node.start_point
        return f"{self.filename}:{start_point[0]+1}:{start_point[1]+1}"

    def _get_end(self, node) -> str:
        end_byte, end_point = node.end_byte, node.end_point
        return f"{self.filename}:{end_point[0]+1}:{end_point[1]+1}"

    def _get_range(self, node) -> str:
        """Get the range for the entire target object."""
        start_pos = self._get_start(node)
        end_pos = self._get_end(node)
        return f"{start_pos} -> {end_pos}"

    @abstractmethod
    def _get_func_params(self, node) -> list:
        """Extract function parameters."""
        return []

    def _extract_base_type(self, node) -> str:
        """Extract the base type."""
        pass

    def _extract_real_type(self, node) -> str:
        """Extract the real type."""
        pass

    def _extract_type(self, node) -> str:
        """Extract the type of the parameter."""
        pass

    @abstractmethod
    def _get_return_type(self, node: Node) -> dict:
        """Extract the return type of the function."""
        return {
            "baseType": "struct ngiflibSDL_animation",
            "isBuiltin": False,
            "isFuncPointer": False,
            "isTemplateType": False,
            "realType": "struct ngiflibSDL_animation *",
            "type": "struct ngiflibSDL_animation *",
        }

    @abstractmethod
    def _get_composites_type(self, node) -> str:
        pass

    @abstractmethod
    def _is_pub(self, node: Node) -> bool:
        pass

    def get(self) -> dict:
        return {
            "classes": self.classes,
            "functions": self.functions,
            "composites": self.composites,
            "enums": self.enums,
            "typedefs": self.typedefs,
        }

    def dump(self, output_path: Path):
        """
        Dump the ast data to a file.

        :param output_path: The output path.
        """
        dict_meta = self.get()
        with open(output_path, "w") as f:
            json.dump(dict_meta, f, indent=4)


class RustParser(BaseParser):
    """
    A simple AST Parser for Rust lang using tree_sitter
    """

    def __init__(self, path_file):
        super().__init__(path_file, RUST_LANGUAGE)

    def _get_func_params(self, node: Node) -> list:
        params = []

        def _extract_func_param(param: Node) -> dict:
            name = None
            type = None
            for _ in param.children:
                if _.type == "identifier":
                    name = _.text.decode()
                elif _.type == "type_identifier":
                    type = _.text.decode()
            return {
                "baseType": None,
                "isBuiltin": None,  # Assuming basic types are built-in
                "isFuncPointer": False,  # Rust does not have function pointers in the same way
                "isTemplateType": False,  # Rust does not have templates
                "name": name,
                "realType": None,
                "type": type,
            }

        for child in node.children:
            if child.type == "parameters":
                for _ in child.children:
                    # "(", "parameter", ",", "parameter", ")"
                    if _.type == "parameter":
                        params.append(_extract_func_param(_))
                break
        return params

    def _func_info(self, node: Node):
        start_pos = self._get_start(node)
        locRange = self._get_range(node)
        self.functions[start_pos] = {
            "name": self._get_name(node),
            "declLoc": None,
            "declLocRange": None,
            "heldbyClass": "",
            "heldbyNamespace": "",
            "locRange": locRange,
            "param": self._get_func_params(node),
            "return": self._get_return_type(node),
            "templateParamNum": 0,  # Assuming no template parameters for Rust
            "isPub": self._is_pub(node),
        }

    def _get_composites_name(self, node: Node) -> str:
        for child in node.children:
            if child.type == "type_identifier":
                return child.text.decode()
        logger.warning(f"No name for {node.text}")
        return None

    def _get_composites_type(self, node) -> str:
        for child in node.children:
            if child.type in ["struct", "union"]:
                return child.type
        logger.error("No composites")
        return None

    def _get_members(self, node: Node) -> list:
        members = []
        for child in node.children:
            if child.type == "field_declaration_list":
                break
        else:
            logger.error(f"Can not find members in {node.text}")
        members_node = child
        for member_node in members_node.children:
            if member_node.type == "field_declaration":
                member = {
                    "name": None,
                    "locRange": self._get_range(member_node),
                    "isPublic": None,
                    "type": None,
                    "realType": None,
                    "baseType": None,
                    "isBuiltin": None,
                    "isFuncPointer": None,
                    "isTemplateType": None,
                }
                for _ in member_node.children:
                    if _.type == ":":
                        member["name"] = _.prev_sibling.text.decode()
                        member["type"] = _.next_sibling.text.decode()
                members.append(member)
        return members

    def _composites_info(self, node: Node):
        """Store struct/union information"""
        start_pos = self._get_start(node)
        loc_range = self._get_range(node)

        self.composites[start_pos] = {
            "name": self._get_composites_name(node),
            "locRange": loc_range,
            "kind": self._get_composites_type(node),
            "templateParamNum": 0,
            "members": self._get_members(node),
            "heldbyNamespace": None,
            "heldbyClass": None,
        }

    def _enum_info(self, node: Node):
        start_pos = self._get_start(node.prev_sibling.prev_sibling)
        loc_range = self._get_range_2(node.prev_sibling.prev_sibling, node)
        self.enums[start_pos] = {
            "name": node.prev_sibling.text.decode(),
            "locRange": loc_range,
            "heldbyNamespace": None,
            "heldbyClass": None,
        }

    def _type_info(self, node: Node):
        start_pos = self._get_start(node)
        loc_range = self._get_range(node)
        for child in node.children:
            if child.type == "type_identifier":
                name = child.text.decode()
            elif child.type == "=":
                type = child.next_sibling.text.decode()
                break

        self.typedefs[start_pos] = {
            "heldbyClass": None,
            "heldbyNamespace": None,
            "locRange": loc_range,
            "name": name,
            "underlyingType": {
                "baseType": None,
                "isBuiltin": None,
                "isFuncPointer": False,
                "isTemplateType": False,
                "realType": None,
                "type": type,
            },
        }

    def _traverse(self, node: Node):
        for child in node.children:
            if child.type == "function_item":
                self._func_info(child)
                continue
            elif child.type == "struct_item":
                self._composites_info(child)
                continue
            elif child.type == "enum_variant_list":
                self._enum_info(child)
                continue
            elif child.type == "type_item":
                self._type_info(child)
                continue
            # print(self.depth, child.type)
            # print(child.text)
            # print("---")
            self.depth += 1
            self._traverse(child)
        self.depth -= 1

    def _is_pub(self, node: Node):
        """Extract the whether target object is pub."""
        for child in node.children:
            if child.type == "visibility_modifier":
                if child.text.decode() == "pub":
                    return True
        return False

    def _parse_type_arguments(self, node: Node):
        print(node.child_count)
        for child in node.children:
            print(f"_parse_type_arguments: type: {child.type}, ctx: {child.text}")
            print("---")

    def _get_return_type(self, node: Node):
        for child in node.children:
            if child.type == "->":
                # Directly process the next child after "->"
                child = child.next_sibling
                return {
                    "baseType": None,
                    "isBuiltin": None,
                    "isFuncPointer": False,
                    "isTemplateType": False,
                    "realType": None,
                    "type": child.text.decode(),
                }
                # for _child in child.children:
                #     print(f"_get_return_type: type: {_child.type}, ctx: {_child.text}")
                #     if _child.type == "type_arguments":
                #         self._parse_type_arguments(_child)
                #     print("---")
        return {}

    def _get_range_2(self, node1, node2) -> str:
        """Get the range for the 2 target objects."""
        start_pos = self._get_start(node1)
        end_pos = self._get_end(node2)
        return f"{start_pos} -> {end_pos}"


if __name__ == "__main__":
    import sys

    path_file = Path(sys.argv[1]).resolve()
    if not path_file.exists():
        raise FileExistsError(f"{path_file} not exist")
    rust_code = path_file.read_text()

    parser = RustParser(path_file)
    parser.parse()
    parser.dump(path_file.parent / f"{path_file.name}.json")
