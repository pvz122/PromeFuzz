#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Extract covered APIs from Fuzz Drivers using Tree Sitter.
This script functions the same as `extract_covered_APIs.py` but is implemented in Tree Sitter,
which is sufficient for C code but may not be suitable for C++ code.
"""

import tree_sitter_c, tree_sitter_cpp
from tree_sitter import Language, Parser, Node, Query, Tree
import click
from pathlib import Path
import json
import chardet
from functools import cache

C_LANGUAGE = Language(tree_sitter_c.language())
CPP_LANGUAGE = Language(tree_sitter_cpp.language())


def load_apis(api_json: Path) -> set[str]:
    """
    Load the API information from the JSON file

    :param api_json: The JSON file containing the API information
    :return: A set of API names
    """
    with api_json.open("r") as f:
        api_info: dict[str, dict[str, list]] = json.load(f)
    api_names = set()
    for file, apis in api_info.items():
        for api_name, locations in apis.items():
            api_names.add(api_name)
            if "::" in api_name:
                # also add the last part of the qualified name
                # e.g. Namespace::Class::method -> method
                # so that we can match the callee name
                # as tree-sitter will return the last part of the qualified name
                api_names.add(api_name.split("::")[-1])

    return api_names


def parse_source_code(source_file: Path) -> tuple[Language, Node]:
    """
    Parse the source code and return the language and root node

    :param source_file: The source file path
    :return: The language and root node of the parsed tree
    """
    # check the source file language
    C_SOURCE_SUFFIX = [".c"]
    CPP_SOURCE_SUFFIX = [".cpp", ".hpp", ".cc", ".hh", ".h", ".cxx", ".hxx"]
    if source_file.suffix in C_SOURCE_SUFFIX:
        language = C_LANGUAGE
    elif source_file.suffix in CPP_SOURCE_SUFFIX:
        language = CPP_LANGUAGE
    else:
        raise ValueError(f"Unsupported source file type: {source_file.suffix}")

    # read the source file
    with source_file.open("rb") as f:
        source_code_bytes = f.read()

    # create the parser
    parser = Parser(language)

    # parse the source code
    encoding = chardet.detect(source_code_bytes)["encoding"]
    if encoding is not None and encoding != "utf-8":
        source_code_bytes = source_code_bytes.decode(encoding).encode("utf-8")
    tree: Tree = parser.parse(source_code_bytes)

    return language, tree.root_node


def get_callees(root: Node, language: Language):
    """
    Get all the callee names from the root node

    :param root: The root node
    :param language: The tree sitter language object
    :return: The generator of callee name and its location
    """
    # query the call expressions
    query = Query(language, "(call_expression) @call")
    try:
        call_expressions = query.captures(root)["call"]
    except:
        return

    for node in call_expressions:
        # get the callee name
        callee_node = node.child_by_field_name("function")
        if not callee_node:
            continue
        if callee_node.type == "field_expression":
            # obj.method()
            callee_name = callee_node.child_by_field_name("field").text
        elif callee_node.type == "pointer_expression":
            # ptr->method()
            callee_name = callee_node.child_by_field_name("field").text
        elif callee_node.type == "qualified_identifier":
            # Namespace::Class::method()
            current = callee_node
            while current.type == "qualified_identifier":
                current = current.child_by_field_name("name")
            callee_name = current.text
        else:
            # plain_func()
            callee_name = callee_node.text

        yield callee_name.decode(), f"{callee_node.start_point.row}:{callee_node.start_point.column}"

@cache
def _get_file_content_lines(source_file: Path) -> list[str]:
    """
    Get the lines of the source file content

    :param source_file: The source file path
    :return: The list of lines in the source file
    """
    with source_file.open("r") as f:
        return f.readlines()

def get_line_content(source_file: Path, line_col: str) -> str:
    """
    Get the line content from the source file based on the line and column

    :param source_file: The source file path
    :param line_col: The line and column in the format "line:column"
    :return: The line content
    """
    line, col = map(int, line_col.split(":"))
    lines = _get_file_content_lines(source_file)
    if 0 <= line < len(lines):
        return lines[line].strip()
    return ""  # Return empty string if the line is out of range

@click.command(help="Extract Covered APIs from C/C++ Fuzz Driver")
@click.option(
    "-a",
    "--api",
    "api_json",
    type=click.Path(path_type=Path, resolve_path=True, exists=True, dir_okay=False),
    help="The JSON file containing the API information.",
    required=True,
)
@click.argument(
    "source_files",
    type=click.Path(path_type=Path, exists=True, dir_okay=False, resolve_path=True),
    nargs=-1,
    required=True,
)
def extract(
    api_json: Path,
    source_files: list[Path],
):
    api_names = load_apis(api_json)

    # result dict is like:
    # {
    #     "total_count": 13,
    #     "source_files": {
    #         "source_file": {
    #             "count": 10,
    #             "callees": {
    #                 "callee_name": {
    #                     "location": "line_content",
    #                     "location": "line_content",
    #                 },
    #             },
    #         },
    #     },
    # }
    result = {"total_count": 0, "source_files": {}}
    total_count = 0
    already_tested_funcs = set()
    for source_file in source_files:
        source_result = {"count": 0, "callees": {}}
        result["source_files"][str(source_file)] = source_result
        count = 0

        # parse the source code
        language, root = parse_source_code(source_file)
        # get the callees
        for callee_name, location in get_callees(root, language):
            if callee_name in api_names:
                # this is a covered API
                if callee_name not in source_result["callees"]:
                    count += 1
                    if callee_name not in already_tested_funcs:
                        already_tested_funcs.add(callee_name)
                        total_count += 1
                    source_result["callees"][callee_name] = {}
                source_result["callees"][callee_name][f"{source_file.name}:{location}"] = get_line_content(source_file, location)
        source_result["count"] = count
        result["total_count"] = total_count

    # print and save the result
    print(f"Total covered APIs: {total_count}, extracted from {len(source_files)} source files, saved to result.json")
    with (Path.cwd() / "result.json").open("w") as f:
        json.dump(result, f, indent=4)



if __name__ == "__main__":
    extract()
