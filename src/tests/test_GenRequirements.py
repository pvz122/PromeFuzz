from src.generator.extractor import CGenRequirements, CppGenRequirements
from src.generator.prompter import Prompter

from pathlib import Path

this_dir = Path(__file__).parent


def run():
    c_gr = CGenRequirements(
        ["void foo();", "void bar();", "void baz();"],
        ["struct A { int a; };", "struct B { int b; };"],
        ["typedef struct { int c; } C;", "typedef struct { int d; } D;"],
    )
    c_gr.update_headers(["/path/to/header1.h", "/path/to/header2.h"])

    # simulate prompter
    c_pr = (this_dir / ".." / "generator" / "prompt" / "gen_c_user").read_text()
    c_pr = c_pr.format(
        LIBRARY_NAME=c_gr.library_name,
        FUNCTION_SIGNATURES=Prompter.format_code(c_gr.function_signatures),
        HEADERS=c_gr.headers,
        DATA_DEFINITIONS=Prompter.format_code(c_gr.data_definitions),
    )

    print(c_pr)


    cpp_gr = CppGenRequirements(
        [
            ("void foo();", "my_namespace", "my_class"),
            ("void bar();", "my_namespace", "my_class"),
            ("void baz();", "my_namespace", "my_class2"),
            ("void qux();", "my_namespace2", "my_class2"),
        ],
        [
            ("struct A { int a; };", "my_namespace", "my_class"),
            ("struct B { int b; };", "my_namespace", "my_class"),
            ("struct C { int c; };", "my_namespace", "my_class2"),
            ("struct D { int d; };", "my_namespace2", "my_class2"),
        ],
        [
            ("typedef struct { int e; } E;", "my_namespace", "my_class"),
            ("typedef struct { int f; } F;", "my_namespace", "my_class"),
            ("typedef struct { int g; } G;", "my_namespace", "my_class2"),
            ("typedef struct { int h; } H;", "my_namespace2", "my_class2"),
        ],
        [
            ("void foo();", "my_namespace", "my_class"),
            ("void bar();", "my_namespace", "my_class"),
            ("void baz();", "my_namespace", "my_class2"),
            ("void qux();", "my_namespace2", "my_class2"),

        ]
    )
    cpp_gr.update_headers(["/path/to/header1.hpp", "/path/to/header2.hpp"])

    # simulate prompter
    cpp_pr = (this_dir / ".." / "generator" / "prompt" / "gen_cpp_user").read_text()
    cpp_pr = cpp_pr.format(
        LIBRARY_NAME=cpp_gr.library_name,
        FUNCTION_SIGNATURES=Prompter.format_code(cpp_gr.function_signatures),
        HEADERS=cpp_gr.headers,
        DATA_DEFINITIONS=Prompter.format_code(cpp_gr.data_definitions),
        CONSTRUCTOR_SIGNATURES=Prompter.format_code(cpp_gr.constructor_signatures),
    )

    print(cpp_pr)