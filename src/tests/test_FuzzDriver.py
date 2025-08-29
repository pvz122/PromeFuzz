from src.generator.driver import FuzzDriver
from src import vars as global_vars

from pathlib import Path

def run():
    global_vars.library_config["driver_build_args"] = []
    global_vars.library_language = global_vars.SupportedLanguages.CPP
    test_fuzz_driver = FuzzDriver(
        """
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    return 0;
}
        """,
        None,
        [("src/tests/pugixml.hpp", "function_name", "location")]
    )
    print(test_fuzz_driver.id)
    print(test_fuzz_driver.build_cmd)
    print(test_fuzz_driver.fuzz_driver_code)
    print(test_fuzz_driver.build(extra_build_args=["useless"]))
    print(test_fuzz_driver.build())
    test_fuzz_driver.save(Path("/tmp"), save_build_script=True, add_comment="// test comment")
    print(test_fuzz_driver.run(extra_build_args=["useless"]))
    print(test_fuzz_driver.run(timeout=1))

    crash_fuzz_driver = FuzzDriver(
        """
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    __builtin_trap();
    return 0;
}
        """,
        None,
        [("src/tests/pugixml.hpp", "function_name", "location")]
    )
    print(crash_fuzz_driver.run())