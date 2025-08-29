#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Build libraries for fuzzing experiments.

This script builds libraries in the database with support for AddressSanitizer,
GCOV coverage analysis, and AFL++ instrumentation.
"""
from loguru import logger
from pathlib import Path
import subprocess
import click
from typing import Optional

from utils import get_aflpp, list_libraries, libraries


# Global paths
DATABASE_PATH = Path(__file__).parent.parent.resolve()
AFLPP_PATH = get_aflpp()

# Build targets
BUILD_TARGETS = ["normal", "asan", "gcov", "cov", "aflpp"]


def build_library(lib_name: str, force_rebuild: bool = False) -> bool:
    """
    Build a specific library with multiple build configurations.

    Args:
        lib_name: Name of the library to build
        force_rebuild: If True, rebuild even if already exists

    Returns:
        bool: True if build was successful, False otherwise
    """
    path_library = DATABASE_PATH / lib_name
    latest_path = path_library / "latest"

    if latest_path.exists() and not force_rebuild:
        logger.warning(
            f"Build directory '{latest_path}' already exists. Skipping build for {lib_name}"
        )
        return True

    try:
        # Install dependencies if needed
        if not _install_dependencies(path_library, lib_name):
            return False

        # Fetch the source code
        if not _fetch_source_code(path_library, lib_name):
            return False

        # Build with different configurations
        if not _build_configurations(latest_path, lib_name):
            return False

        logger.success(f"Successfully built {lib_name}")
        return True

    except Exception as e:
        logger.error(f"Unexpected error while building {lib_name}: {e}")
        return False


def _install_dependencies(path_library: Path, lib_name: str) -> bool:
    """Install library dependencies if install script exists."""
    dep_script = path_library / "install_deps.sh"
    if dep_script.exists():
        try:
            logger.info(f"Installing dependencies for {lib_name}...")
            subprocess.run(["bash", str(dep_script)], check=True)
            logger.info(f"Dependencies installed for {lib_name}")
        except subprocess.CalledProcessError as e:
            logger.error(f"Failed to install dependencies for {lib_name}: {e}")
            return False
    return True


def _fetch_source_code(path_library: Path, lib_name: str) -> bool:
    """Fetch source code using the fetch script."""
    fetch_script = path_library / "fetch.sh"
    if not fetch_script.exists():
        logger.critical(f"Fetch script '{fetch_script}' does not exist for {lib_name}")
        return False

    commit_id = libraries.get(lib_name, "")
    try:
        logger.info(f"Fetching source code for {lib_name}...")
        subprocess.run(["bash", "./fetch.sh", commit_id], check=True, cwd=path_library)
        logger.info(f"Source code fetched for {lib_name}")
        return True
    except subprocess.CalledProcessError as e:
        logger.error(f"Failed to fetch source code for {lib_name}: {e}")
        return False


def _build_configurations(build_dir_path: Path, lib_name: str) -> bool:
    """Build library with different configurations (asan, gcov, aflpp)."""
    build_script = build_dir_path / "build.sh"
    if not build_script.exists():
        logger.critical(f"Build script '{build_script}' does not exist for {lib_name}")
        return False

    for target in BUILD_TARGETS:
        try:
            logger.info(f"Building {lib_name} with {target.upper()}...")
            subprocess.run(["bash", "build.sh", target], check=True, cwd=build_dir_path)
            logger.info(f"Successfully built {lib_name} with {target.upper()}")
        except subprocess.CalledProcessError as e:
            logger.error(f"Failed to build {lib_name} with {target}: {e}")
            return False

    return True


@click.command()
@click.argument("mode", type=click.Choice(["one", "all"]))
@click.argument("library_name", required=False)
@click.option(
    "--force", "-f", is_flag=True, help="Force rebuild even if library already exists"
)
def main(mode: str, library_name: Optional[str], force: bool) -> None:
    """
    Build libraries for fuzzing experiments.

    MODE: Choose 'one' to build a specific library or 'all' to build all libraries.
    LIBRARY_NAME: Required when MODE is 'one'. Specify which library to build.
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

        success = build_library(library_name, force_rebuild=force)
        if not success:
            exit(1)

    elif mode == "all":
        failed_libraries = []
        for library in list_libraries:
            logger.info(f"Building library: {library}")
            success = build_library(library, force_rebuild=force)
            if not success:
                failed_libraries.append(library)

        if failed_libraries:
            logger.warning(f"Failed to build libraries: {', '.join(failed_libraries)}")
            exit(1)
        else:
            logger.success("Successfully built all libraries")


if __name__ == "__main__":
    main()
