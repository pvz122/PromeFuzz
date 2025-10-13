#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Run fuzzing experiments for libraries.

This script executes fuzzing campaigns for libraries in the database using AFL++
with configurable timeouts and output paths.
"""
from loguru import logger
from pathlib import Path
import subprocess
import click
from typing import Optional

from utils import get_aflpp, list_libraries, aflpp_args


# Global configuration
DATABASE_PATH = Path(__file__).parent.parent.resolve()
DEFAULT_TIMEOUT_HOURS = 24
DEFAULT_FUZZER = "aflpp"
DEFAULT_IDENTIFICATION = "promefuzz"

# TOML template for fuzz configuration
FUZZ_CONFIG_TEMPLATE = """[aflpp]
fuzzer_path = "{afl_path}"
timeout = "{timeout}"

[{lib_name}]
[{lib_name}.latest.{identification}]
fuzzer = "{fuzzer}"
bin = "./{lib_name}/latest/out/fuzz_driver/aflpp_synthesized_driver"
bin_asan = "./{lib_name}/latest/out/fuzz_driver/aflpp_synthesized_driver"
bin_gcov = "./{lib_name}/latest/out/fuzz_driver/gcov_synthesized_driver"
build_gcov = "./{lib_name}/latest/build_gcov"
out_base_path = "./{lib_name}/latest/fuzz"
in_path = "./{lib_name}/in"
aflpp_args = "{aflpp_args}"
cmd = "@@"
"""


def run_fuzz_campaign(
    lib_name: str,
    timeout_hours: int = DEFAULT_TIMEOUT_HOURS,
    identification: str = DEFAULT_IDENTIFICATION,
) -> bool:
    """
    Run a fuzzing campaign for a specific library.

    Args:
        lib_name: Name of the library to fuzz
        timeout_hours: Fuzzing timeout in hours
        identification: Identification string for the campaign

    Returns:
        bool: True if fuzzing started successfully, False otherwise
    """
    try:
        # Get AFL++ path
        aflpp_path = get_aflpp()

        # Validate library structure
        if not _validate_library_structure(lib_name):
            return False

        # Generate fuzz configuration
        config_path = _generate_fuzz_config(
            lib_name, aflpp_path, timeout_hours, identification
        )
        if not config_path:
            return False

        # Execute fuzzing
        return _execute_fuzzing(lib_name, config_path, identification)

    except Exception as e:
        logger.error(f"Failed to run fuzzing campaign for {lib_name}: {e}")
        return False


def _validate_library_structure(lib_name: str) -> bool:
    """Validate that the library has the required structure for fuzzing."""
    path_library = DATABASE_PATH / lib_name
    latest_dir = path_library / "latest"
    driver_dir = latest_dir / "out" / "fuzz_driver"
    input_dir = path_library / "in"

    missing_paths = []

    if not latest_dir.exists():
        missing_paths.append(str(latest_dir))
    if not driver_dir.exists():
        missing_paths.append(str(driver_dir))
    if not input_dir.exists():
        missing_paths.append(str(input_dir))

    if missing_paths:
        logger.error(
            f"Missing required directories for {lib_name}: {', '.join(missing_paths)}"
        )
        return False

    # Check for required binaries
    aflpp_driver = driver_dir / "aflpp_synthesized_driver"
    gcov_driver = driver_dir / "gcov_synthesized_driver"

    if not aflpp_driver.exists():
        logger.error(f"AFL++ driver not found: {aflpp_driver}")
        return False

    if not gcov_driver.exists():
        logger.warning(f"GCOV driver not found: {gcov_driver}")

    logger.info(f"Library structure validated for {lib_name}")
    return True


def _generate_fuzz_config(
    lib_name: str, aflpp_path: Path, timeout_hours: int, identification: str
) -> Optional[Path]:
    """Generate fuzz configuration file for the library."""
    try:
        driver_dir = DATABASE_PATH / lib_name / "latest" / "out" / "fuzz_driver"
        config_path = driver_dir / "fuzz.toml"

        config_content = FUZZ_CONFIG_TEMPLATE.format(
            afl_path=aflpp_path / "afl-fuzz",
            lib_name=lib_name,
            timeout=timeout_hours,
            fuzzer=DEFAULT_FUZZER,
            aflpp_args=aflpp_args.get(lib_name, ""),
            identification=identification,
        )

        config_path.write_text(config_content)
        logger.info(f"Generated fuzz config: {config_path}")
        return config_path

    except Exception as e:
        logger.error(f"Failed to generate fuzz config for {lib_name}: {e}")
        return None


def _execute_fuzzing(lib_name: str, config_path: Path, identification: str) -> bool:
    """Execute the fuzzing process."""
    try:
        fuzz_script = DATABASE_PATH / "utils" / "fuzz.py"

        if not fuzz_script.exists():
            logger.error(f"Fuzz script not found: {fuzz_script}")
            return False

        fuzz_cmd = [
            str(fuzz_script),
            "-c",
            str(config_path),
            "-p",
            lib_name,
            "-v",
            "latest",
            "-fi",
            identification,
        ]

        logger.info(
            f"Starting fuzzing for {lib_name} with command: {' '.join(fuzz_cmd)}"
        )
        subprocess.run(fuzz_cmd, cwd=DATABASE_PATH, check=True)
        logger.success(f"Fuzzing started successfully for {lib_name}")
        return True

    except subprocess.CalledProcessError as e:
        logger.error(f"Fuzzing process failed for {lib_name}: {e}")
        return False
    except Exception as e:
        logger.error(f"Unexpected error during fuzzing execution for {lib_name}: {e}")
        return False


@click.command()
@click.argument("mode", type=click.Choice(["one", "all"]))
@click.argument("library_name", required=False)
@click.option(
    "--timeout", "-t", default=DEFAULT_TIMEOUT_HOURS, help="Fuzzing timeout in hours"
)
@click.option(
    "--identification",
    "-i",
    default=DEFAULT_IDENTIFICATION,
    help="Campaign identification string",
)
def main(
    mode: str, library_name: Optional[str], timeout: int, identification: str
) -> None:
    """
    Run fuzzing experiments for libraries.

    MODE: Choose 'one' to fuzz a specific library or 'all' to fuzz all libraries.
    LIBRARY_NAME: Required when MODE is 'one'. Specify which library to fuzz.
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

        success = run_fuzz_campaign(library_name, timeout, identification)
        if not success:
            logger.error(f"Failed to start fuzzing for {library_name}")
            exit(1)

    elif mode == "all":
        failed_libraries = []
        successful_libraries = []

        for lib in list_libraries:
            logger.info(f"Starting fuzzing campaign for {lib}")
            success = run_fuzz_campaign(lib, timeout, identification)

            if success:
                successful_libraries.append(lib)
            else:
                failed_libraries.append(lib)

        # Report results
        if successful_libraries:
            logger.success(
                f"Successfully started fuzzing for: {', '.join(successful_libraries)}"
            )
        if failed_libraries:
            logger.warning(
                f"Failed to start fuzzing for: {', '.join(failed_libraries)}"
            )
            exit(1)
        else:
            logger.success("All fuzzing campaigns started successfully")


if __name__ == "__main__":
    main()
