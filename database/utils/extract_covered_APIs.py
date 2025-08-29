#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Extract covered APIs from Fuzz Drivers using ClangAST-based cgprocessor.
"""

import click
from pathlib import Path
import json
import sys
import shutil
import subprocess
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import cpu_count
from tempfile import TemporaryDirectory
from tqdm import tqdm

# Ensure the src directory is in the Python path
sys.path.append(str(Path(__file__).absolute().parent.parent.parent))

from src.preprocessor.api import APICollection, APIFunction

CGPROCESSOR_BIN = (
    Path(__file__).absolute().parent.parent.parent / "build/bin/cgprocessor"
)


def get_build_args(build_script: Path) -> str:
    """
    Get the build command arguments from the build script.

    :param build_script: The build script path
    :return: The build arguments as a string
    """
    # The build script is like:
    # #! /bin/bash
    # cd /home/pvz122/proj/llm/abl-afgenllm
    # clang++ /home/pvz122/proj/llm/abl-afgenllm/database/libtiff/latest/out-ofg/fuzz_driver/fuzz_driver_1.cpp -o /home/pvz122/proj/llm/abl-afgenllm/database/libtiff/latest/out-ofg/fuzz_driver/fuzz_driver_1 -fsanitize=fuzzer,address,undefined -g -I/home/pvz122/proj/llm/abl-afgenllm/database/libtiff/latest/code/libtiff -Idatabase/libtiff/latest/bin_asan/include database/libtiff/latest/bin_asan/lib/libtiff.a database/libtiff/latest/bin_asan/lib/libtiffxx.a -lz -ljpeg -ljbig -llzma -lzstd

    # We only need the part after "-fsanitize"
    build_script_content = build_script.read_text()
    truncate_index = build_script_content.find("-fsanitize")
    if truncate_index == -1:
        raise ValueError(
            f"Invalid build script: {build_script}. No '-fsanitize' found."
        )
    build_args = build_script_content[truncate_index:].strip()
    return build_args


def extract_fuzz_driver_apis(
    api_collection: APICollection, source_file: Path, build_args: str, tmp_dir: Path
) -> list[APIFunction]:
    """
    Extract covered APIs from a fuzz driver source file using the cgprocessor.

    :param api_collection: The API collection to check against
    :param source_file: The source file path
    :param build_args: The build arguments for the cgprocessor
    :param tmp_dir: The temporary directory to store the output
    :return: A list of covered APIs
    """
    cg_result_path = tmp_dir / f"{source_file.stem}_cg.json"
    cmd = f"{CGPROCESSOR_BIN} {source_file} -o {cg_result_path} -- {build_args}"
    try:
        output = subprocess.check_output(
            cmd, stderr=subprocess.STDOUT, shell=True, text=True
        )
    except subprocess.CalledProcessError as e:
        print(f"Error running CGprocessor for {source_file}: {e.output}")
        return []

    # load the CGprocessor output
    try:
        calling_info: dict[str, dict[str, str]] = json.loads(cg_result_path.read_text())
    except Exception as e:
        print(f"Failed to load CGprocessor output for fuzz driver {source_file}: {e}")
        return []

    # check the target API functions
    target_apis = []
    for _, calling in calling_info.items():
        target = api_collection.get_by_decl_location(calling["calleeDeclLoc"])
        if target:
            target_apis.append(target)

    return target_apis


@click.command(help="Extract Covered APIs from C/C++ Fuzz Driver")
@click.option(
    "-a",
    "--api",
    "api_pkl",
    type=click.Path(path_type=Path, resolve_path=True, exists=True, dir_okay=False),
    help="The PKL file containing the API information.",
    required=True,
)
@click.argument(
    "driver_dir",
    type=click.Path(path_type=Path, exists=True, dir_okay=True, resolve_path=True),
    required=True,
)
def extract(
    api_pkl: Path,
    driver_dir: Path,
):
    api_collection = APICollection.load(api_pkl)
    driver_files = list(driver_dir.glob("fuzz_driver_*.c")) + list(
        driver_dir.glob("fuzz_driver_*.cpp")
    )
    if not driver_files:
        print(f"No fuzz driver found in {driver_dir}.")
        sys.exit(1)
    try:
        build_script = list(driver_dir.glob("build_fuzz_driver_*.sh"))[0]
    except IndexError:
        print(f"No build script found in {driver_dir}.")
        sys.exit(1)
    build_args = get_build_args(build_script)

    with TemporaryDirectory(
        dir=(
            "/dev/shm"
            if (
                Path("/dev/shm").exists()
                and shutil.disk_usage("/dev/shm").free >= 1073741824
            )
            else None
        )
    ) as tmp_dir:
        progress_bar = tqdm(
            total=len(driver_files),
            desc="Extracting covered APIs",
            unit="driver",
            leave=False,
        )
        extract_one = lambda source_file: (
            source_file,
            extract_fuzz_driver_apis(
                api_collection, source_file, build_args, Path(tmp_dir)
            ),
            progress_bar.update(1),
        )
        with ThreadPoolExecutor(max_workers=cpu_count()) as executor:
            results = list(executor.map(extract_one, driver_files))
        progress_bar.close()

    results = [(y[0], y[1]) for y in sorted(results, key=lambda x: str(x[0]))]

    result = {"total_count": 0, "source_files": {}}
    all_covered_apis = set()
    for source_file, apis in results:
        source_result = {"count": len(apis), "callees": [str(api) for api in apis]}
        result["source_files"][str(source_file)] = source_result
        all_covered_apis.update(apis)
    result["total_count"] = len(all_covered_apis)

    print(
        f"Total covered APIs: {result['total_count']}, extracted from {len(driver_files)} source files. Results saved to {driver_dir / 'covered_apis.json'}"
    )
    with (driver_dir / "covered_apis.json").open("w") as f:
        json.dump(result, f, indent=4)


if __name__ == "__main__":
    if not CGPROCESSOR_BIN.exists():
        print(
            f"Error: cgprocessor binary not found at {CGPROCESSOR_BIN}. Please build it first."
        )
        sys.exit(1)
    extract()
