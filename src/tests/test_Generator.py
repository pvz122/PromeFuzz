from src.generator.generator import Generator
from src.preprocessor.information import InfoRepository
from src.generator.llm import DummyClient
from src import vars as global_vars

from pathlib import Path


def run():
    global_vars.library_language = global_vars.SupportedLanguages.C
    llm_client = DummyClient()

    cJSON_info_path = Path("out/cJSON/preprocessor/info.pkl")
    if not cJSON_info_path.exists():
        print("This test requires cJSON info at out/cJSON/preprocessor/info.pkl")
        return

    c_info = InfoRepository.load(cJSON_info_path)
    c_generator = Generator(llm_client, c_info)

    target_functions = [
        (
            "/promefuzz/library/cJSON/cJSON.h",
            "cJSON_Print",
            "/promefuzz/library/cJSON/cJSON.c:1275:22",
        ),
        (
            "/promefuzz/library/cJSON/cJSON.h",
            "cJSON_Parse",
            "/promefuzz/library/cJSON/cJSON.c:1195:23",
        ),
        (
            "/promefuzz/library/cJSON/cJSON.h",
            "cJSON_malloc",
            "/promefuzz/library/cJSON/cJSON.c:3145:22",
        ),
        (
            "/promefuzz/library/cJSON/cJSON.h",
            "cJSON_free",
            "/promefuzz/library/cJSON/cJSON.c:3150:20",
        ),
    ]
    c_driver = c_generator.generate(target_functions)
    print(c_driver.fuzz_driver_code)

    global_vars.library_language = global_vars.SupportedLanguages.CPP

    pugi_info_path = Path("out/pugixml/preprocessor/info.pkl")
    if not pugi_info_path.exists():
        print("This test requires pugixml info at out/pugixml/preprocessor/info.pkl")
        return

    cpp_info = InfoRepository.load(pugi_info_path)
    target_functions = [
        (
            "/promefuzz/library/pugixml/src/pugixml.hpp",
            "pugi::xpath_exception::result",
            "/promefuzz/library/pugixml/src/pugixml.cpp:12399:58",
        ),
        (
            "/promefuzz/library/pugixml/src/pugixml.hpp",
            "pugi::xpath_variable::set",
            "/promefuzz/library/pugixml/src/pugixml.cpp:12668:36",
        ),
        (
            "/promefuzz/library/pugixml/src/pugixml.hpp",
            "pugi::xml_node::insert_copy_before",
            "/promefuzz/library/pugixml/src/pugixml.cpp:5993:39",
        ),
    ]
    cpp_generator = Generator(llm_client, cpp_info)
    cpp_driver = cpp_generator.generate(target_functions)
    print(cpp_driver.fuzz_driver_code)
