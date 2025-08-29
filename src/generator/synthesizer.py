#! /usr/bin/env python3
"""
Synthesize all fuzz drivers into one.
"""

from pathlib import Path
import shutil
import sys
from functools import cached_property


class IndividualDriver:
    """
    Class for an individual fuzz driver.
    """

    def __init__(self, driver_path: Path):
        """
        Initialize an IndividualDriver object with a fuzz driver file.

        :param driver_path: Path to the fuzz driver file.
        """
        self.driver_path = driver_path

    @property
    def content(self) -> str:
        """
        The content of the fuzz driver.
        """
        return self.driver_path.read_text()

    @property
    def modified_content(self) -> str:
        """
        The modified content of the fuzz driver.
        """
        return self.content.replace(
            "LLVMFuzzerTestOneInput(", f"LLVMFuzzerTestOneInput_{self.id}("
        )

    @property
    def build_script(self) -> str:
        """
        The build script of the fuzz driver.
        """
        return (
            self.driver_path.parent / f"build_{self.driver_path.stem}.sh"
        ).read_text()

    @cached_property
    def id(self) -> str:
        """
        The ID of the fuzz driver.
        """
        return self.driver_path.name.split("_")[-1].split(".")[0]

    @property
    def suffix(self) -> str:
        """
        The suffix of the fuzz driver file.
        """
        return self.driver_path.suffix[1:]


class SynthesizedDriver:
    """
    Class for the synthesized fuzz driver.
    """

    def __init__(self, drivers: list[IndividualDriver]):
        """
        Create a synthesized fuzz driver from a list of individual fuzz drivers.

        :param drivers: List of IndividualDriver objects.
        """
        self.drivers = sorted(drivers, key=lambda driver: int(driver.id))

    @classmethod
    def from_dir(cls, driver_dir: Path):
        """
        Create a synthesized fuzz driver from all fuzz drivers in a directory.

        :param driver_dir: Path to the directory containing the fuzz drivers.
        """
        drivers = [
            IndividualDriver(driver_path)
            for driver_path in driver_dir.glob("fuzz_driver_*.c")
        ]
        if not drivers:
            drivers = [
                IndividualDriver(driver_path)
                for driver_path in driver_dir.glob("fuzz_driver_*.cpp")
            ]
        if not drivers:
            raise FileNotFoundError(
                f"No fuzz driver files found in the directory {driver_dir}"
            )
        return cls(drivers)

    @cached_property
    def driver_count(self) -> int:
        """
        The number of fuzz drivers.
        """
        return len(self.drivers)

    @cached_property
    def is_cpp(self) -> bool:
        """
        Whether the synthesized driver is in C++.
        """
        return self.drivers[0].suffix in ["cpp", "cc", "cxx"]

    @cached_property
    def entry_driver(self) -> str:
        """
        Get the entry driver code of the synthesized driver.
        """

        def indication_comment() -> str:
            """
            The indication comment listing all fuzz drivers.
            """
            content = f"// This is the entry of {self.driver_count} fuzz drivers:\n"
            driver_id_str = ", ".join(str(driver.id) for driver in self.drivers)
            for sliced_id_str in [
                driver_id_str[i : i + 80] for i in range(0, len(driver_id_str), 80)
            ]:
                content += f"// {sliced_id_str}\n"
            return content.strip()

        def fuzzer_declarations() -> str:
            """
            The declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions.
            """
            content = "// Declarations of all fuzz drivers `LLVMFuzzerTestOneInput` functions\n"
            for driver in self.drivers:
                content += f"{'extern "C" ' if self.is_cpp else ''}int LLVMFuzzerTestOneInput_{driver.id}(const uint8_t *Data, size_t Size);\n"
            return content

        def headers() -> str:
            """
            The headers of the synthesized driver.
            """
            HEADERS = [
                "stdint.h",
                "stddef.h",
                "unistd.h",
                "memory.h",
            ]
            return "\n".join([f"#include <{header}>" for header in HEADERS]) + "\n"

        def fuzzer_selector() -> str:
            """
            The driver selector code.
            """
            driver_count_bits = self.driver_count.bit_length()
            driver_count_bytes = (driver_count_bits + 7) // 8  # floor to byte-aligned

            # prepare data and size
            content = """// Driver selector
    if (Size < {offset}) {{
        return 0;
    }}
    const uint8_t *selector = Data;
    unsigned int driverIndex = 0;
    memcpy(&driverIndex, selector, {offset});

    // Remain data and size
    const uint8_t *remainData = Data + {offset};
    size_t remainSize = Size - {offset};
    if (remainSize == 0) {{
        return 0;
    }}

    // Select driver
    switch (driverIndex % {driver_count}) {{""".format(
                offset=driver_count_bytes, driver_count=self.driver_count
            )

            # add driver cases
            for i, driver in enumerate(self.drivers):
                content += """
        case {i}:
            return LLVMFuzzerTestOneInput_{id}(remainData, remainSize);""".format(
                    i=i, id=driver.id
                )
            content += """
        default:
            return 0;
    }"""

            return content

        def entry() -> str:
            """
            The entry function of the synthesized driver.
            """
            return """// Entry function
{cpp}int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {{
    {driver_selector}
    return 0;
}}
""".format(
                cpp='extern "C" ' if self.is_cpp else "",
                driver_selector=fuzzer_selector(),
            )

        return "\n".join(
            [
                indication_comment(),
                headers(),
                fuzzer_declarations(),
                entry(),
            ]
        )

    def build_script(self, save_path: Path) -> str:
        """
        The build script of the synthesized driver.

        :param save_path: Path to save the synthesized driver.
        """
        # The build script of an individual driver is like:

        # #! /bin/bash
        # cd /promefuzz
        # clang++ /promefuzz/database/pugixml/latest/out/fuzz_driver/fuzz_driver_1.cpp \
        # -o /promefuzz/database/pugixml/latest/out/fuzz_driver/fuzz_driver_1 \
        # -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/pugixml/latest/code/src \
        # database/pugixml/latest/bin_asan/lib/libpugixml.a

        # We replace the driver file path with `save_path/synthesized/{id}.{suffix}` + `entry.{suffix}`
        # and the output file path with `save_path/synthesized_driver`

        base_script = self.drivers[0].build_script.split("\n")
        result_script = []
        # find the xxx/fuzz_driver_xxx.xxx argument
        for line in base_script:
            if not line.startswith("clang"):
                result_script.append(line)
                continue

            # this is the clang command
            base_args = line.split(" ")
            result_args = []
            flag_output = False
            for arg in base_args:
                if arg.endswith(
                    f"fuzz_driver_{self.drivers[0].id}.{self.drivers[0].suffix}"
                ):
                    result_args.append(
                        str(
                            save_path / f"synthesized/*.{'cpp' if self.is_cpp else 'c'}"
                        )
                    )
                    continue
                elif arg == "-o":
                    flag_output = True
                elif flag_output:
                    # this is the output file path
                    result_args.append(str(save_path / "synthesized_driver"))
                    flag_output = False
                    continue
                result_args.append(arg)
            result_script.append(" ".join(result_args))

        return "\n".join(result_script)

    def save(self, save_path: Path):
        """
        Save the synthesized driver to a file.

        :param save_path: Path to save the synthesized driver.
        """
        save_path = save_path.resolve()
        driver_dir = save_path / "synthesized"
        if driver_dir.exists():
            shutil.rmtree(driver_dir)
        driver_dir.mkdir(parents=True, exist_ok=True)

        # save the entry driver
        (driver_dir / f"entry.{'cpp' if self.is_cpp else 'c'}").write_text(
            self.entry_driver
        )

        # save individual drivers
        for driver in self.drivers:
            (driver_dir / f"{driver.id}.{'cpp' if self.is_cpp else 'c'}").write_text(
                driver.modified_content
            )

        # save the build script
        (save_path / "build_synthesized_driver.sh").write_text(
            self.build_script(save_path)
        )
        (save_path / "build_synthesized_driver.sh").chmod(0o755)

        # convert to aflpp, gcov and cov build script
        gen_additional_script(save_path / "build_synthesized_driver.sh")


def copy_synthesizer_to(driver_dir: Path):
    """
    Copy this script to the directory of fuzz drivers.

    :param driver_dir: Path to the directory containing the fuzz drivers.
    """
    target_path = driver_dir / "synthesize_into_one"
    shutil.copy(__file__, target_path)
    target_path.chmod(0o755)


def gen_additional_script(primary_build_script_path: Path):
    script_content = primary_build_script_path.read_text()
    script_content_lines = script_content.split("\n")
    cd_cmd = next(line for line in script_content_lines if line.startswith("cd"))
    old_compile_args = next(
        line for line in script_content_lines if line.startswith("clang")
    ).split(" ")

    # for aflpp
    # process the compile command
    out_arg_flag = False
    aflpp_compile_args = list()
    for i, compile_cmd in enumerate(old_compile_args):
        # replace clang with afl-clang-fast
        if compile_cmd == "clang" or compile_cmd == "clang++":
            aflpp_compile_args.append(
                f"AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast{'++' if compile_cmd == 'clang++' else ''}"
            )
        elif compile_cmd == "-o":
            out_arg_flag = True
            out_path = Path(old_compile_args[i + 1])
            out_path = out_path.parent / f"aflpp_{out_path.name}"
            aflpp_compile_args.append(
                f"-o {str(out_path).replace("_asan", "_aflpp")} $AFLPP_LIB_PATH"
            )
        elif compile_cmd.startswith("-fsanitize=fuzzer"):
            out_arg_flag = False
        elif out_arg_flag:
            pass
        else:
            aflpp_compile_args.append(compile_cmd.replace("_asan", "_aflpp"))

    # for gcov
    out_arg_flag = False
    gcov_compile_args = list()
    for i, compile_cmd in enumerate(old_compile_args):
        if compile_cmd == "-o":
            out_arg_flag = True
            out_path = Path(old_compile_args[i + 1])
            out_path = out_path.parent / f"gcov_{out_path.name}"
            gcov_compile_args.append(f"-o {str(out_path).replace("_asan", "_gcov")}")
        elif compile_cmd.startswith("-fsanitize=fuzzer"):
            out_arg_flag = False
            gcov_compile_args.append("--coverage -fsanitize=fuzzer")
        elif out_arg_flag:
            pass
        else:
            gcov_compile_args.append(compile_cmd.replace("_asan", "_gcov"))

    # for cov
    out_arg_flag = False
    cov_compile_args = list()
    for i, compile_cmd in enumerate(old_compile_args):
        if compile_cmd == "-o":
            out_arg_flag = True
            out_path = Path(old_compile_args[i + 1])
            out_path = out_path.parent / f"cov_{out_path.name}"
            cov_compile_args.append(f"-o {str(out_path).replace("_asan", "_cov")}")
        elif compile_cmd.startswith("-fsanitize=fuzzer"):
            out_arg_flag = False
            cov_compile_args.append(
                "-fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer"
            )
        elif out_arg_flag:
            pass
        else:
            cov_compile_args.append(compile_cmd.replace("_asan", "_cov"))

    # generate separate build scripts for each fuzzer type

    # aflpp build script
    aflpp_script_content = """#! /bin/bash
{get_aflpp_path}
{cd_cmd}
{aflpp_compile_cmd}""".format(
        get_aflpp_path="""if [ -z "$AFLPP_PATH" ]; then
    AFL_CLANG_FAST_PATH=$(command -v afl-clang-fast)
    if [ -z "$AFL_CLANG_FAST_PATH" ]; then
        echo "Please install AFL++ and set AFLPP_PATH" && exit 1
    fi
    AFLPP_PATH=$(dirname "$AFL_CLANG_FAST_PATH")
    AFLPP_LIB_PATH=$(dirname "$AFLPP_PATH")/lib/afl/libAFLDriver.a
else
    AFLPP_LIB_PATH=$AFLPP_LIB_PATH
fi
""",
        cd_cmd=cd_cmd,
        aflpp_compile_cmd=" ".join(aflpp_compile_args),
    )

    # gcov build script
    gcov_script_content = """#! /bin/bash
{cd_cmd}
{gcov_compile_cmd}""".format(
        cd_cmd=cd_cmd,
        gcov_compile_cmd=" ".join(gcov_compile_args),
    )

    # cov build script
    cov_script_content = """#! /bin/bash
{cd_cmd}
{cov_compile_cmd}""".format(
        cd_cmd=cd_cmd,
        cov_compile_cmd=" ".join(cov_compile_args),
    )

    # write the scripts to the same directory as the libfuzzer build script
    base_name = primary_build_script_path.name.removeprefix("build_")

    aflpp_script_path = primary_build_script_path.parent / f"build_aflpp_{base_name}"
    aflpp_script_path.write_text(aflpp_script_content)
    aflpp_script_path.chmod(0o755)

    gcov_script_path = primary_build_script_path.parent / f"build_gcov_{base_name}"
    gcov_script_path.write_text(gcov_script_content)
    gcov_script_path.chmod(0o755)

    cov_script_path = primary_build_script_path.parent / f"build_cov_{base_name}"
    cov_script_path.write_text(cov_script_content)
    cov_script_path.chmod(0o755)


if __name__ == "__main__":
    """
    Run the synthesizer from the command line.

    Usage: synthesizer.py [driver_dir]
    """
    if len(sys.argv) < 2:
        driver_dir = Path(__file__).parent.resolve()
    else:
        driver_dir = Path(sys.argv[1]).resolve()
    synthesized_driver = SynthesizedDriver.from_dir(driver_dir)
    synthesized_driver.save(driver_dir)
    print("Done.")
