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
from enum import StrEnum, auto


from utils import list_libraries, load_config_file, save_config_file


# Global paths
DATABASE_PATH = Path(__file__).parent.parent.resolve()
PROMEFUZZ_DIR = DATABASE_PATH.parent


# Ablation settings
class ABLATION(StrEnum):
    NONE = auto()
    WO_COMP = auto()
    WO_SCHD = auto()
    WO_SAN = auto()
    WEIGHT_COV = auto()
    WEIGHT_REL = auto()
    WEIGHT_TYP = auto()
    WEIGHT_SCP = auto()
    WEIGHT_EQ1 = auto()
    WEIGHT_EQ2 = auto()


WEIGHTS_CONFIG = {
    ABLATION.NONE.name: {
        "type_relevance": 2,
        "class_scope_relevance": 1,
        "call_scope_relevance": 3,
        "semantic_relevance": 5,
        "coverage": 3,
        "relevance": 1,
    },
    ABLATION.WEIGHT_COV.name: {
        "type_relevance": 2,
        "class_scope_relevance": 1,
        "call_scope_relevance": 3,
        "semantic_relevance": 5,
        "coverage": 5,
        "relevance": 1,
    },
    ABLATION.WEIGHT_REL.name: {
        "type_relevance": 2,
        "class_scope_relevance": 1,
        "call_scope_relevance": 3,
        "semantic_relevance": 5,
        "coverage": 1,
        "relevance": 3,
    },
    ABLATION.WEIGHT_TYP.name: {
        "type_relevance": 5,
        "class_scope_relevance": 1,
        "call_scope_relevance": 3,
        "semantic_relevance": 2,
        "coverage": 3,
        "relevance": 1,
    },
    ABLATION.WEIGHT_SCP.name: {
        "type_relevance": 2,
        "class_scope_relevance": 5,
        "call_scope_relevance": 5,
        "semantic_relevance": 3,
        "coverage": 3,
        "relevance": 1,
    },
    ABLATION.WEIGHT_EQ1.name: {
        "type_relevance": 2,
        "class_scope_relevance": 1,
        "call_scope_relevance": 3,
        "semantic_relevance": 5,
        "coverage": 1,
        "relevance": 1,
    },
    ABLATION.WEIGHT_EQ2.name: {
        "type_relevance": 1,
        "class_scope_relevance": 1,
        "call_scope_relevance": 1,
        "semantic_relevance": 1,
        "coverage": 1,
        "relevance": 1,
    },
}


def _run_and_check(cmd: str) -> bool:
    """
    Run a shell command and check its success.

    :param cmd: The command to run.
    :return: True if the command was successful, False otherwise.
    """
    result = subprocess.run(cmd, shell=True)
    return result.returncode == 0


def generate(
    lib_name: str, ablation: str, promefuzz_config: Path | None = None
) -> bool:
    """
    Generate fuzz drivers for the specified library.

    :param lib_name: The name of the library to generate fuzz drivers for.
    :param ablation: The ablation setting, if any.
    :param promefuzz_config: Optional path to a custom PromeFuzz configuration file.
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
    abl_arg = ""
    if ablation == ABLATION.WO_COMP.name:
        abl_arg = " --disable comprehender"
    elif ablation == ABLATION.WO_SCHD.name:
        abl_arg = " --disable scheduler"
    elif ablation == ABLATION.WO_SAN.name:
        abl_arg = " --disable sanitizer"
    pconfig_arg = f" --config {promefuzz_config}" if promefuzz_config else ""

    cmd = f"./PromeFuzz.py{pconfig_arg} -F {LIB_TOML} generate{abl_arg}"
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


def set_weights(ablation: str) -> Path:
    """
    Set the weights in the configuration file based on the ablation setting.

    :param ablation: The ablation setting.
    :return: Path to the temporary configuration file with updated weights.
    """
    config_path = PROMEFUZZ_DIR / "config.toml"
    temp_config = Path(f"./config_{ablation}.toml")

    config_data = load_config_file(config_path)
    config_data.setdefault("generator", dict())["schedule_weights"] = WEIGHTS_CONFIG[
        ablation
    ]
    save_config_file(temp_config, config_data)
    return temp_config.resolve()


def generate_and_build(lib_name: str, ablation: str) -> bool:
    """
    Generate fuzz drivers for the specified library and build the generated drivers.

    :param lib_name: The name of the library to generate fuzz drivers for.
    :param ablation: The ablation setting, if any.
    :return: True if the generation and building were successful, False otherwise.
    """
    if ablation in [ABLATION.WO_COMP.name, ABLATION.WO_SCHD.name, ABLATION.WO_SAN.name]:
        return generate(lib_name, ablation) and build(lib_name)
    elif ablation in [
        ABLATION.WEIGHT_COV.name,
        ABLATION.WEIGHT_REL.name,
        ABLATION.WEIGHT_TYP.name,
        ABLATION.WEIGHT_SCP.name,
        ABLATION.WEIGHT_EQ1.name,
        ABLATION.WEIGHT_EQ2.name,
    ]:
        temp_config = set_weights(ablation)
        return generate(
            lib_name, ABLATION.NONE.name, promefuzz_config=temp_config
        ) and build(lib_name)
    else:
        return generate(lib_name, ABLATION.NONE.name) and build(lib_name)


@click.command()
@click.argument("mode", type=click.Choice(["one", "all"]))
@click.argument("library_name", required=False)
@click.argument(
    "ablation",
    required=False,
    type=click.Choice([e.name for e in ABLATION]),
    default=ABLATION.NONE.name,
)
def main(mode: str, library_name: Optional[str], ablation: str):
    """
    Use PromeFuzz to generate fuzz drivers and build the generated drivers.

    MODE: Choose 'one' to generate fuzz drivers for a specific library
          or 'all' generate fuzz drivers for libraries in the dataset.
    LIBRARY_NAME: Required when MODE is 'one'. Specify which library to generate fuzz driver.
    ABLATION: Optional. Specify the ablation setting if any.
    """
    if not ablation == ABLATION.NONE.name:
        logger.info(f"Using ablation setting: {ablation}")

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

        success = generate_and_build(library_name, ablation)
        if not success:
            exit(1)

    elif mode == "all":
        failed_libraries = []
        for library in list_libraries:
            logger.info(f"Generate fuzz drivers for {library}...")
            success = generate_and_build(library, ablation)
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
