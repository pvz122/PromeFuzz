from src.generator.extractor import (
    CInfoExtractor,
    CppInfoExtractor,
    CGenRequirements,
    CppGenRequirements,
)
from src.generator.prompter import Prompter
from src.preprocessor.information import InfoRepository

from pathlib import Path

this_dir = Path(__file__).parent


def run():
    cJSON_info_path = Path("out/cJSON/preprocessor/info.pkl")
    if not cJSON_info_path.exists():
        print("This test requires cJSON info at out/cJSON/preprocessor/info.pkl")
        return

    c_info = InfoRepository.load(cJSON_info_path)

    test_case_1 = [
        "/promefuzz/library/cJSON/cJSON_Utils.c:1038:19",
        "/promefuzz/library/cJSON/cJSON_Utils.c:1281:23",
        "/promefuzz/library/cJSON/cJSON_Utils.c:1316:20",
        "/promefuzz/library/cJSON/cJSON_Utils.c:348:23",
        "/promefuzz/library/cJSON/cJSON.c:1275:22",
    ]
    test_case_2 = [
        "/promefuzz/library/cJSON/cJSON.c:1946:23",
        "/promefuzz/library/cJSON/cJSON.c:1951:26",
        "/promefuzz/library/cJSON/cJSON.c:209:20",
        "/promefuzz/library/cJSON/cJSON.c:2192:22",
        "/promefuzz/library/cJSON/cJSON.c:2326:26",
        "/promefuzz/library/cJSON/cJSON_Utils.c:1386:23",
    ]
    test_case_3 = [
        "/promefuzz/library/cJSON/cJSON.c:99:22",
        "/promefuzz/library/cJSON/cJSON.c:94:28",
        "/promefuzz/library/cJSON/cJSON.c:3000:26",
        "/promefuzz/library/cJSON/cJSON.c:2980:26",
    ]

    def test_c(test_case):
        extractor = CInfoExtractor(c_info)
        result = extractor.extract_generation_specific_info(test_case)
        prompt = (this_dir / ".." / "generator" / "prompt" / "gen_c_user").read_text()
        prompt = prompt.format(
            LIBRARY_NAME=result.library_name,
            FUNCTION_SIGNATURES=Prompter.format_code(result.function_signatures),
            HEADERS=result.headers,
            DATA_DEFINITIONS=Prompter.format_code(result.data_definitions),
        )
        print(prompt)

    print("====================== C Test Case 1 ======================")
    test_c(test_case_1)
    print("====================== C Test Case 2 ======================")
    test_c(test_case_2)
    print("====================== C Test Case 3 ======================")
    test_c(test_case_3)

    pugi_info_path = Path("out/pugixml/preprocessor/info.pkl")
    if not pugi_info_path.exists():
        print("This test requires pugixml info at out/pugixml/preprocessor/info.pkl")
        return

    cpp_info = InfoRepository.load(pugi_info_path)

    test_case_1 = [
        "/promefuzz/library/pugixml/src/pugixml.cpp:12566:38",
        "/promefuzz/library/pugixml/src/pugixml.cpp:12571:36",
        "/promefuzz/library/pugixml/src/pugixml.cpp:12592:36",
        "/promefuzz/library/pugixml/src/pugixml.cpp:12863:40",
        "/promefuzz/library/pugixml/src/pugixml.cpp:12869:40",
        "/promefuzz/library/pugixml/src/pugixml.cpp:5493:35",
    ]
    test_case_2 = [
        "/promefuzz/library/pugixml/src/pugixml.cpp:5522:35",
        "/promefuzz/library/pugixml/src/pugixml.cpp:5571:44",
        "/promefuzz/library/pugixml/src/pugixml.cpp:6045:34",
        "/promefuzz/library/pugixml/src/pugixml.cpp:6712:31",
        "/promefuzz/library/pugixml/src/pugixml.cpp:6788:30",
        "/promefuzz/library/pugixml/src/pugixml.hpp:319:6",
    ]
    test_case_3 = [
        "/promefuzz/library/pugixml/src/pugixml.hpp:645:42",
        "/promefuzz/library/pugixml/src/pugixml.hpp:621:47",
        "/promefuzz/library/pugixml/src/pugixml.cpp:12587:62",
        "/promefuzz/library/pugixml/src/pugixml.cpp:13094:39",
        "/promefuzz/library/pugixml/src/pugixml.cpp:5281:44",
    ]

    def test_cpp(test_case):
        extractor = CppInfoExtractor(cpp_info)
        result = extractor.extract_generation_specific_info(test_case)
        prompt = (this_dir / ".." / "generator" / "prompt" / "gen_cpp_user").read_text()
        prompt = prompt.format(
            LIBRARY_NAME=result.library_name,
            FUNCTION_SIGNATURES=Prompter.format_code(result.function_signatures),
            HEADERS=result.headers,
            DATA_DEFINITIONS=Prompter.format_code(result.data_definitions),
            CONSTRUCTOR_SIGNATURES=Prompter.format_code(result.constructor_signatures),
        )
        print(prompt)

    print("====================== C++ Test Case 1 ======================")
    test_cpp(test_case_1)
    print("====================== C++ Test Case 2 ======================")
    test_cpp(test_case_2)
    print("====================== C++ Test Case 3 ======================")
    test_cpp(test_case_3)