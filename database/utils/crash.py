#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Collect crashes from the fuzzing results.
"""
from loguru import logger
from pathlib import Path
import click
import tomllib
import sys
from multiprocessing import cpu_count
from concurrent.futures import ThreadPoolExecutor
import subprocess
import shutil
import tqdm
import tempfile


@click.command(help="Collect crashes from the fuzzing results.")
@click.option(
    "--config",
    "-c",
    help="Path to the fuzz.toml configuration file",
    type=click.Path(path_type=Path, exists=True),
    default=Path(__file__).parent / "fuzz.toml",
)
@click.option(
    "--project", "-p", required=True, help="The name of the project, e.g., ngiflib"
)
@click.option(
    "--version", "-v", required=True, help="The version of the project, e.g., latest"
)
@click.option(
    "--fuzz-id",
    "-fi",
    "fuzz_id",
    required=True,
    help="The identification name of the fuzz target, e.g., promefuzz",
)
@click.option(
    "--pool-size",
    "pool_size",
    type=int,
    default=cpu_count(),
    help="The pool size to reproduce the crashes.",
)
def collect_crashes(
    config: Path, project: str, version: str, fuzz_id: str, pool_size: int
):
    """
    Collect crashes from the fuzzing results.
    """
    logger.remove()
    logger.add(
        tqdm.tqdm.write,
        level="INFO",
        format="<green>{time:YYYY-MM-DD HH:mm:ss}</green> | <level>{level}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> | <level>{message}</level>",
        colorize=True,
    )

    config_dict = tomllib.loads(config.read_text())
    try:
        target_config = config_dict[project][version][fuzz_id]
    except KeyError:
        logger.critical(f"{project}.{version}.{fuzz_id} not in fuzz config")
        sys.exit(-1)

    crash_files = get_crash_files(target_config, fuzz_id)
    fuzz_cmd = get_fuzz_cmd_from_config(target_config)
    logger.info(f"Found {len(crash_files)} crash files")
    logger.info(f"Using fuzz command: {fuzz_cmd}")

    progress_bar = tqdm.tqdm(
        total=len(crash_files),
        desc="Reproducing crashes",
        unit="crash",
        leave=False,
        colour="yellow",
    )

    # reproduce the crashes
    def reproduce_crash(crash_file: Path) -> str:
        with tempfile.TemporaryDirectory(
            dir=(
                "/dev/shm"
                if (
                    Path("/dev/shm").exists()
                    and shutil.disk_usage("/dev/shm").free >= 1073741824
                )
                else None
            )
        ) as tmpdir:
            cmd = f"{fuzz_cmd.replace("@@", str(crash_file.resolve(strict=True)))}"
            logger.debug(f"Reproducing {crash_file}")
            try:
                ret = subprocess.run(
                    cmd,
                    cwd=tmpdir,
                    shell=True,
                    capture_output=True,
                    text=True,
                    timeout=120,
                    errors="replace",
                )
            except subprocess.TimeoutExpired:
                logger.error(f"Timeout for {crash_file} with command: {cmd}")
                return ""
            finally:
                progress_bar.update(1)

        return ret.stdout + "\n" + ret.stderr

    if pool_size == 1:
        crash_msgs = [reproduce_crash(crash_file) for crash_file in crash_files]
    else:
        with ThreadPoolExecutor(pool_size) as executor:
            crash_msgs = list(executor.map(reproduce_crash, crash_files))

    # save the crash messages
    crash_dir = Path(f"{project}/{version}/crashes")
    if crash_dir.exists():
        shutil.rmtree(crash_dir)
    crash_dir.mkdir(parents=True, exist_ok=True)

    for i, crash_msg, crash_file in zip(
        range(len(crash_msgs)), crash_msgs, crash_files
    ):
        (crash_dir / f"{i}.log").write_text(crash_msg)
        shutil.copy(crash_file, crash_dir / f"{i}.input")

    logger.success(
        f"{len(crash_msgs)} crashes are saved to {crash_dir.resolve()}, you may want to run `analyze` to analyze them."
    )


def get_crash_files(target_config: dict, fuzz_id: str) -> list[Path]:
    """
    Get the crash files from the fuzzing results.

    :param target_config: The target configuration dictionary.
    :param fuzz_id: The identification name of the fuzz target.
    :return: The list of crash files
    """
    # the crashes are stored in the out_base_path/out_{fuzz_id}_{timeout}_{idx}/out/default/crashes
    result_path = Path(target_config["out_base_path"])
    if not result_path.exists():
        logger.critical(f"{result_path} does not exist")
        sys.exit(-1)

    out_folders = result_path.glob(f"out_{fuzz_id}_*")
    crash_files: list[Path] = []
    for out_folder in out_folders:
        crash_files.extend(out_folder.glob("out/default/crashes/*"))

    # remove "README.txt"
    crash_files = [
        crash_file
        for crash_file in crash_files
        if not crash_file.name.startswith("README")
    ]
    return crash_files


def get_fuzz_cmd_from_config(target_config: dict) -> str:
    """'
    Get the fuzz command from the config.

    :param target_config: The target configuration dictionary.
    :return: The fuzz command, like:
    ```
    ASAN_OPTIONS='symbolize=1:detect_odr_violation=0:allocator_may_return_null=1' ../ngiflib/latest/out/fuzz_driver/aflpp_synthesized_driver @@
    ```
    """
    return " ".join(
        [
            "ASAN_OPTIONS='symbolize=1:detect_odr_violation=0:allocator_may_return_null=1'",
            str(Path(target_config["bin_asan"]).resolve()),
            target_config["cmd"],
        ]
    )


if __name__ == "__main__":
    collect_crashes()
