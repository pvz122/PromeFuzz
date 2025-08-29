#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Run GCOV coverage analysis for libraries.

This script executes GCOV coverage collection for libraries in the database
after fuzzing campaigns to analyze code coverage achieved.
"""
from loguru import logger
from pathlib import Path
import subprocess
import click
from typing import Optional

from utils import get_aflpp, list_libraries


# Global configuration
DATABASE_PATH = Path(__file__).parent.parent.resolve()
DEFAULT_POST_SLEEP = 30  # seconds to wait after fuzzing completion
DEFAULT_IDENTIFICATION = "promefuzz"

# TOML template for GCOV configuration
GCOV_CONFIG_TEMPLATE = """[aflpp]
fuzzer_path = "{afl_path}"
timeout = "{timeout}"

[{lib_name}]
[{lib_name}.latest.{identification}]
fuzzer = "aflpp"
bin = "./{lib_name}/latest/out/fuzz_driver/aflpp_synthesized_driver"
bin_asan = "./{lib_name}/latest/out/fuzz_driver/aflpp_synthesized_driver"
bin_gcov = "./{lib_name}/latest/out/fuzz_driver/gcov_synthesized_driver"
build_gcov = "./{lib_name}/latest/build_gcov"
out_base_path = "./{lib_name}/latest/fuzz"
in_path = "./{lib_name}/in"
cmd = "@@"
"""


def run_gcov_analysis(
    lib_name: str,
    post_sleep: int = DEFAULT_POST_SLEEP,
    identification: str = DEFAULT_IDENTIFICATION,
) -> bool:
    """
    Run GCOV coverage analysis for a specific library.

    Args:
        lib_name: Name of the library to analyze
        post_sleep: Time to wait after fuzzing completion (seconds)
        identification: Identification string for the campaign

    Returns:
        bool: True if GCOV analysis started successfully, False otherwise
    """
    try:
        # Get AFL++ path
        aflpp_path = get_aflpp()

        # Validate library structure
        if not _validate_library_structure(lib_name):
            return False

        # Generate GCOV configuration
        config_path = _generate_gcov_config(lib_name, aflpp_path, identification)
        if not config_path:
            return False

        # Execute GCOV analysis
        return _execute_gcov_analysis(lib_name, config_path, post_sleep, identification)

    except Exception as e:
        logger.error(f"Failed to run GCOV analysis for {lib_name}: {e}")
        return False


def _validate_library_structure(lib_name: str) -> bool:
    """Validate that the library has the required structure for GCOV analysis."""
    path_library = DATABASE_PATH / lib_name
    latest_dir = path_library / "latest"
    driver_dir = latest_dir / "out" / "fuzz_driver"
    fuzz_dir = latest_dir / "fuzz"

    missing_paths = []

    if not latest_dir.exists():
        missing_paths.append(str(latest_dir))
    if not driver_dir.exists():
        missing_paths.append(str(driver_dir))
    if not fuzz_dir.exists():
        missing_paths.append(str(fuzz_dir))

    if missing_paths:
        logger.error(
            f"Missing required directories for {lib_name}: {', '.join(missing_paths)}"
        )
        return False

    # Check for required binaries
    gcov_driver = driver_dir / "gcov_synthesized_driver"
    build_gcov_dir = latest_dir / "build_gcov"

    if not gcov_driver.exists():
        logger.error(f"GCOV driver not found: {gcov_driver}")
        return False

    if not build_gcov_dir.exists():
        logger.error(f"GCOV build directory not found: {build_gcov_dir}")
        return False

    logger.info(f"Library structure validated for GCOV analysis: {lib_name}")
    return True


def _generate_gcov_config(
    lib_name: str, aflpp_path: Path, identification: str
) -> Optional[Path]:
    """Generate GCOV configuration file for the library."""
    try:
        driver_dir = DATABASE_PATH / lib_name / "latest" / "out" / "fuzz_driver"
        config_path = driver_dir / "fuzz.toml"

        # Check if config already exists, use it if available
        if config_path.exists():
            logger.info(f"Using existing fuzz config: {config_path}")
            return config_path

        # Generate new config if doesn't exist
        config_content = GCOV_CONFIG_TEMPLATE.format(
            afl_path=aflpp_path / "afl-fuzz",
            lib_name=lib_name,
            timeout=24,  # Default timeout for GCOV config
            identification=identification,
        )

        config_path.write_text(config_content)
        logger.info(f"Generated GCOV config: {config_path}")
        return config_path

    except Exception as e:
        logger.error(f"Failed to generate GCOV config for {lib_name}: {e}")
        return None


def _execute_gcov_analysis(
    lib_name: str, config_path: Path, post_sleep: int, identification: str
) -> bool:
    """Execute the GCOV analysis process."""
    try:
        gcov_script = DATABASE_PATH / "utils" / "gcov.py"

        if not gcov_script.exists():
            logger.error(f"GCOV script not found: {gcov_script}")
            return False

        gcov_cmd = [
            str(gcov_script),
            "-c",
            str(config_path),
            "-ps",
            str(post_sleep),
            "-v",
            "latest",
            "-p",
            lib_name,
            "-fi",
            identification,
        ]

        logger.info(
            f"Starting GCOV analysis for {lib_name} with command: {' '.join(gcov_cmd)}"
        )
        subprocess.run(gcov_cmd, cwd=DATABASE_PATH, check=True)
        logger.success(f"GCOV analysis completed successfully for {lib_name}")
        return True

    except subprocess.CalledProcessError as e:
        logger.error(f"GCOV analysis process failed for {lib_name}: {e}")
        return False
    except Exception as e:
        logger.error(f"Unexpected error during GCOV analysis for {lib_name}: {e}")
        return False


@click.command()
@click.argument("mode", type=click.Choice(["one", "all"]))
@click.argument("library_name", required=False)
@click.option(
    "--post-sleep",
    "-ps",
    default=DEFAULT_POST_SLEEP,
    help="Time to wait after fuzzing completion (seconds)",
)
@click.option(
    "--identification",
    "-i",
    default=DEFAULT_IDENTIFICATION,
    help="Campaign identification string",
)
def main(
    mode: str, library_name: Optional[str], post_sleep: int, identification: str
) -> None:
    """
    Run GCOV coverage analysis for libraries.

    MODE: Choose 'one' to analyze a specific library or 'all' to analyze all libraries.
    LIBRARY_NAME: Required when MODE is 'one'. Specify which library to analyze.
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

        success = run_gcov_analysis(library_name, post_sleep, identification)
        if not success:
            logger.error(f"Failed to run GCOV analysis for {library_name}")
            exit(1)

    elif mode == "all":
        failed_libraries = []
        successful_libraries = []

        for lib in list_libraries:
            logger.info(f"Starting GCOV analysis for {lib}")
            success = run_gcov_analysis(lib, post_sleep, identification)

            if success:
                successful_libraries.append(lib)
            else:
                failed_libraries.append(lib)

        # Report results
        if successful_libraries:
            logger.success(
                f"Successfully completed GCOV analysis for: {', '.join(successful_libraries)}"
            )
        if failed_libraries:
            logger.warning(f"Failed GCOV analysis for: {', '.join(failed_libraries)}")
            exit(1)
        else:
            logger.success("All GCOV analyses completed successfully")


if __name__ == "__main__":
    main()
