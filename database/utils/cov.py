#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Run LLVM-Cov to get coverage information.
"""
import os
import json
import subprocess
from pathlib import Path
from loguru import logger
import tomllib
import click
import tqdm
import tempfile
import shutil
from concurrent.futures import ThreadPoolExecutor

from extraction import Extraction


class Cov:
    def __init__(self, config, time_gap=1):
        """
        Initialize LLVM-Cov object

        :param config: The configuration file for the fuzzing project
        :param time_gap: The time gap to run LLVM-Cov
        """
        self.config = config
        self.time_gap = time_gap

    def _is_system(self, file_path) -> bool:
        if "/usr/include" in file_path:
            return True
        return False

    def _parse_cov(self, output: bytes, cov_dir: Path) -> dict:
        METRICS = [
            ("lines", "line"),
            ("branches", "branch"),
            ("functions", "function"),
        ]
        dict_cov = {}
        dict_raw_cov = json.loads(output)
        totals = {out_key: {"covered": 0, "count": 0} for _, out_key in METRICS}

        for file_info in dict_raw_cov["data"][0]["files"]:
            filename = file_info["filename"]
            if str(cov_dir) in filename:
                continue
            if self._is_system(filename):
                continue
            summary = file_info["summary"]
            file_entry = {}
            for json_key, out_key in METRICS:
                metric = summary[json_key]
                covered = metric["covered"]
                count = metric["count"]
                totals[out_key]["covered"] += covered
                totals[out_key]["count"] += count
                file_entry[out_key] = covered
                file_entry[f"{out_key}_all"] = count
            dict_cov[filename] = file_entry

        summary_entry = {out_key: totals[out_key]["covered"] for out_key in totals}
        summary_entry.update(
            {f"{out_key}_all": totals[out_key]["count"] for out_key in totals}
        )
        dict_cov["Summary"] = summary_entry

        return dict_cov

    def run(
        self,
        project_name: str,
        version: str,
        fuzz_id: str,
        out_id: str,
        time: int = 24,
        pool_size: int = 1,
    ):
        """
        Run llvm-cov for a specific fuzz target

        :param project_name: The name of the project, e.g., ngiflib
        :param version: The version of the project, e.g., latest
        :param fuzz_id: The identification name of the fuzz target, e.g., promefuzz
        :param out_id: The start output id of the fuzz target, e.g., promefuzz_24_0
        :param time: The time to run fuzzing in hours, e.g., 24
        :param pool_size: The pool size for the parallel execution
        """
        try:
            config = self.config[project_name][version][fuzz_id]
        except:
            logger.error(f"{project_name}.{version}.{fuzz_id} not in fuzz config")
            return

        prog_arg = config["cmd"]
        afltype = config["fuzzer"]
        out_base_path = Path(config["out_base_path"]).resolve()
        bin_cov = Path(config["bin_cov"]).resolve()

        if not bin_cov.exists():
            logger.error(f"{bin_cov} not exist")
            return

        path_base = out_base_path / f"out_{out_id}"
        workdir = (Path(project_name) / version / "cov" / out_id).resolve()
        profraw_dir = workdir / "profraw"
        data_dir = workdir / "data"
        if workdir.exists():
            logger.warning(f"Already run llvm-cov for {out_id}")
            return
        else:
            workdir.mkdir(parents=True, exist_ok=True)
            profraw_dir.mkdir()
            data_dir.mkdir()

        e = Extraction(project_name, str(path_base), afltype)
        start_time = 1
        list_old_queue = []
        dict_gcov = dict()
        for _time in tqdm.tqdm(
            range(start_time, time + 1, self.time_gap),
            unit="hour",
            desc=f"Running LLVM-Cov for {out_id}",
            leave=False,
        ):
            list_queue = e.extract(_time * 3600, "queue")
            if list_queue == []:
                logger.warning("empty queue list")
                continue
            _list_queue = list(set(list_queue) - set(list_old_queue))
            list_old_queue = list_queue
            _list_queue.sort()

            progress_bar = tqdm.tqdm(
                total=len(_list_queue),
                desc=f"Running the {_time}th hour",
                unit="seed",
                leave=False,
                colour="green",
            )

            def _run_cov(queue):
                cmd = f"{bin_cov} {prog_arg.replace('@@', str(Path(queue).resolve()))}"
                id = Path(queue).name.split(",")[0].split(":")[1]
                cov_raw = profraw_dir / f"{id}.profraw"
                my_env = os.environ
                my_env["LLVM_PROFILE_FILE"] = str(cov_raw)
                with tempfile.TemporaryDirectory(
                    dir=(
                        "/dev/shm"
                        if (
                            Path("/dev/shm").exists()
                            and shutil.disk_usage("/dev/shm").free >= 1073741824
                        )
                        else None
                    )
                ) as cwd:
                    logger.debug(f"running: {cmd}")
                    logger.debug(cov_raw)
                    try:
                        subprocess.run(
                            cmd,
                            shell=True,
                            timeout=30,
                            cwd=cwd,
                            env=my_env,
                            stdout=subprocess.DEVNULL,
                            stderr=subprocess.DEVNULL,
                        )
                    except subprocess.TimeoutExpired:
                        logger.warning(f"run {queue} for more than 30s")
                    finally:
                        progress_bar.update(1)

            if pool_size == 1:
                for queue in _list_queue:
                    _run_cov(queue)
            else:
                with ThreadPoolExecutor(max_workers=pool_size) as executor:
                    executor.map(_run_cov, _list_queue)

            # merge into 1 profdata file
            profdata_file = data_dir / f"{_time}.profdata"
            cmd = f"llvm-profdata merge -sparse {profraw_dir}/* -o {profdata_file}"
            subprocess.run(
                cmd,
                shell=True,
                cwd=workdir,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
            )
            # read profdata file and dump into json file
            cmd = f"llvm-cov export -summary-only {bin_cov} -instr-profile={profdata_file}"
            output = subprocess.run(
                cmd,
                shell=True,
                cwd=workdir,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            raw_cov_path = data_dir / f"cov-raw-{_time}.json"
            raw_cov_path.write_bytes(output.stdout)
            dict_gcov = self._parse_cov(output.stdout, bin_cov.parent)
            cov_path = workdir / f"cov-{_time}.json"
            cov_path.write_text(json.dumps(dict_gcov, indent=2))


@click.command(help="Run LLVM-Cov to get coverage information")
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
    "-ps",
    "pool_size",
    default=1,
    help="The pool size for the parallel execution",
)
def collect_cov(
    config: Path,
    project: str,
    version: str,
    fuzz_id: str,
    pool_size: int,
):
    logger.remove()
    logger.add(
        tqdm.tqdm.write,
        level="INFO",
        format="<green>{time:YYYY-MM-DD HH:mm:ss}</green> | <level>{level}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> | <level>{message}</level>",
        colorize=True,
    )

    config = tomllib.loads(config.read_text())

    cov_path = Path(project) / version / "cov"
    cov_path.mkdir(parents=True, exist_ok=True)
    out_ids = [
        out_folder.name.removeprefix("out_")
        for out_folder in Path(config[project][version][fuzz_id]["out_base_path"]).glob(
            f"out_{fuzz_id}_*"
        )
    ]
    cov = Cov(config)
    for out_id in tqdm.tqdm(
        out_ids, desc="Processing fuzzing results", unit="instance", leave=False
    ):
        cov.run(
            project,
            version,
            fuzz_id,
            out_id,
            pool_size=pool_size,
        )


if __name__ == "__main__":
    collect_cov()
