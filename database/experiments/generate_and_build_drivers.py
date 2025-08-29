#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
This script use PromeFuzz to preprocess, comprehend, and generate, then build the generated drivers.
"""
from loguru import logger
from pathlib import Path
import subprocess
import os
import click
from typing import Optional

from utils import list_libraries


# Global paths
DATABASE_PATH = Path(__file__).parent.parent.resolve()
PROMEFUZZ_DIR = DATABASE_PATH.parent

def _run_and_check(cmd: str) -> bool:
    """
    Run a shell command and check its success.

    :param cmd: The command to run.
    :return: True if the command was successful, False otherwise.
    """
    result = subprocess.run(cmd, shell=True)
    return result.returncode == 0

def generate(lib_name: str) -> bool:
    """
    Generate fuzz drivers for the specified library.

    :param lib_name: The name of the library to generate fuzz drivers for.
    :return: True if the generation was successful, False otherwise.
    """
    os.chdir(PROMEFUZZ_DIR)
    LIB_TOML = DATABASE_PATH / f"{lib_name}/latest/lib.toml"

    logger.info(f"Run preprocessor for {lib_name}...")
    cmd = f"./PromeFuzz.py -F {LIB_TOML} preprocess"
    if not _run_and_check(cmd):
        return False
    
    logger.info(f"Run comprehender for {lib_name}...")
    cmd = f"./PromeFuzz.py -F {LIB_TOML} comprehend --pool-size 50"
    if not _run_and_check(cmd):
        return False

    logger.info(f"Run generator for {lib_name}...")
    cmd = f"./PromeFuzz.py -F {LIB_TOML} generate"
    if not _run_and_check(cmd):
        return False
    
    logger.info(f"Run statistics for {lib_name}...")
    cmd = f"./PromeFuzz.py -F {LIB_TOML} stats"
    if not _run_and_check(cmd):
        return False

    return True

def build(lib_name: str) -> bool:
    """
    Build the generated fuzz drivers for the specified library.

    :param lib_name: The name of the library to build fuzz drivers for.
    :return: True if the building was successful, False otherwise.
    """
    os.chdir(DATABASE_PATH / lib_name / "latest/out/fuzz_driver")
    logger.info(f"Run synthesizer for {lib_name}...")
    cmd = "./synthesize_into_one"
    if not _run_and_check(cmd):
        return False

    logger.info(f"Build synthesized fuzz driver for {lib_name}...")
    for file in Path(".").glob("*synthesized_driver.sh"):
        cmd = f"bash {file}"
        if not _run_and_check(cmd):
            return False

    return True

def generate_and_build(lib_name: str) -> bool:
    """
    Generate fuzz drivers for the specified library and build the generated drivers.

    :param lib_name: The name of the library to generate fuzz drivers for.
    :return: True if the generation and building were successful, False otherwise.
    """
    return generate(lib_name) and build(lib_name)


@click.command()
@click.argument("mode", type=click.Choice(["one", "all"]))
@click.argument("library_name", required=False)
def main(mode: str, library_name: Optional[str]) -> None:
    """
    Use PromeFuzz to generate fuzz drivers and build the generated drivers.

    MODE: Choose 'one' to generate fuzz drivers for a specific library
          or 'all' generate fuzz drivers for libraries in the dataset.
    LIBRARY_NAME: Required when MODE is 'one'. Specify which library to generate fuzz driver.
    """
    if mode == "one":
        if not library_name:
            logger.critical("Please provide the library name when using 'one' mode")
            exit(1)
        if library_name not in list_libraries:
            logger.critical(
                f"'{library_name}' is not a valid library. "
                f"Available libraries: {', '.join(list_libraries)}"
            )
            exit(1)

        success = generate_and_build(library_name)
        if not success:
            exit(1)

    elif mode == "all":
        failed_libraries = []
        for library in list_libraries:
            logger.info(f"Generate fuzz drivers for {library}...")
            success = generate_and_build(library)
            if not success:
                failed_libraries.append(library)

        if failed_libraries:
            logger.warning(
                f"Failed to generate fuzz drivers for: {', '.join(failed_libraries)}"
            )
            exit(1)
        else:
            logger.success("Successfully generate fuzz drivers for all libraries")


if __name__ == "__main__":
    main()
