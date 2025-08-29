#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Run GCov to get coverage information.
"""
import re
import json
import subprocess
from pathlib import Path
from loguru import logger
import tomllib
import click
import tqdm
import tempfile
import shutil
import csv
from functools import cache
from concurrent.futures import ThreadPoolExecutor

from extraction import Extraction


class GCov:
    file_pattern = r"File '([^']+)'"
    data_pattern = r"\d+\.\d+% of \d+"
    cal_pattern = r"([\d.]+)% of (\d+)"

    def __init__(self, config, time_gap=1):
        """
        Initialize GCov object

        :param config: The configuration file for the fuzzing project
        :param is_continue: Whether to continue the previous run
        :param time_gap: The time gap to run GCov
        """
        self.config = config
        self.time_gap = time_gap

    def _is_system(self, file_path) -> bool:
        if "/usr/include" in file_path:
            return True
        return False

    def _clear_gcda(self, gcov_build_path: Path):
        for gcda_file in gcov_build_path.rglob("*.gcda"):
            logger.debug(f"delete {gcda_file}")
            gcda_file.unlink()

    def _parse_gcov(self, output: bytes) -> dict:
        dict_gcov = dict()
        sections = output.split(b"\n\n")
        for section in sections:
            file_match = re.search(self.file_pattern, section.decode())
            if file_match:
                file_path = file_match.group(1)
                if self._is_system(file_path):
                    continue
            else:
                if section != b"":
                    logger.warning(f"No File path in {section}")
                continue
            # Lines cov
            data_matches = re.findall(self.data_pattern, section.decode())
            try:
                lcov_match = re.match(self.cal_pattern, data_matches[0])
                percentage = float(lcov_match.group(1))  # Convert to float
                line_all = int(lcov_match.group(2))  # Convert to integer
                line_cnt = round(line_all * (percentage / 100))
            except:
                line_all = 0
                line_cnt = 0
                logger.error(f"cannot match {data_matches}")

            # Branches cov
            try:
                br_match = re.match(self.cal_pattern, data_matches[1])
                percentage = float(br_match.group(1))  # Convert to float
                br_all = int(br_match.group(2))  # Convert to integer
                br_cnt = round(br_all * (percentage / 100))
            except:
                # logger.error(f"cannot match branch from {output.decode()}")
                br_all = 0
                br_cnt = 0

            dict_gcov[file_path] = {
                "line": line_cnt,
                "branch": br_cnt,
                "line_all": line_all,
                "branch_all": br_all,
            }
        return dict_gcov

    def run(
        self,
        project_name: str,
        version: str,
        fuzz_id: str,
        out_id: str,
        time: int = 24,
        is_header_lib: bool = False,
        exclude_src: list[str] = [],
        pool_size: int = 1,
    ):
        """
        Run gcov for a specific fuzz target

        :param project_name: The name of the project, e.g., ngiflib
        :param version: The version of the project, e.g., latest
        :param fuzz_id: The identification name of the fuzz target, e.g., promefuzz
        :param out_id: The start output id of the fuzz target, e.g., promefuzz_24_0
        :param time: The time to run fuzzing in hours, e.g., 24
        :param is_header_lib: Whether the fuzz target is a header library
        :param exclude_src: The source paths to exclude from the coverage report
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
        bin_gcov = Path(config["bin_gcov"])
        if not is_header_lib:
            build_gcov = Path(config["build_gcov"])
        else:
            build_gcov = bin_gcov.parent

        if not bin_gcov.exists():
            logger.error(f"{bin_gcov} not exist")
            return

        path_base = out_base_path / f"out_{out_id}"
        workdir = (Path(project_name) / version / "gcov" / out_id).resolve()

        if workdir.exists():
            logger.warning(f"Already run gcov for {out_id}")
            return
        else:
            workdir.mkdir(parents=True, exist_ok=True)

        exclude_src = [Path(src).resolve() for src in exclude_src]

        @cache
        def _in_exclude(src_file: str) -> bool:
            src_path = Path(src_file)
            if not src_path.is_absolute():
                src_path = (build_gcov / src_path).resolve()
            for exclude_path in exclude_src:
                if src_path.is_relative_to(exclude_path):
                    return True
            return False

        self._clear_gcda(build_gcov)

        e = Extraction(project_name, str(path_base), afltype)
        start_time = 1
        list_old_queue = []
        result_cov_dict = dict()
        for _time in range(start_time, time + 1, self.time_gap):
            list_queue = e.extract(_time * 3600, "queue")
            if list_queue == []:
                logger.warning("empty queue list")
                continue
            _list_queue = list(set(list_queue) - set(list_old_queue))
            _list_queue.sort()
            list_old_queue = list_queue

            progress_bar = tqdm.tqdm(
                total=len(_list_queue),
                desc=f"Running GCov for {out_id} for hour {_time}",
                unit="seed",
                leave=False,
                colour="green",
            )

            def _run_gcov(queue):
                cmd = f"{bin_gcov.resolve()} {prog_arg.replace('@@', str(Path(queue).resolve()))}"
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
                    try:
                        subprocess.run(
                            cmd,
                            shell=True,
                            timeout=30,
                            cwd=cwd,
                            stdout=subprocess.DEVNULL,
                            stderr=subprocess.DEVNULL,
                        )
                    except subprocess.TimeoutExpired:
                        logger.warning(f"run {queue} for more than 30s")
                    finally:
                        progress_bar.update(1)

            if pool_size == 1:
                for queue in _list_queue:
                    _run_gcov(queue)
            else:
                with ThreadPoolExecutor(max_workers=pool_size) as executor:
                    executor.map(_run_gcov, _list_queue)

            line_cnt = 0
            br_cnt = 0
            line_all = 0
            br_all = 0
            result_cov_dict = dict()
            for gcda_file in build_gcov.rglob("*.gcda"):
                cmd = (
                    f"llvm-cov gcov {gcda_file.resolve()} {bin_gcov.resolve()} -b -c -n"
                )
                output = subprocess.run(
                    cmd,
                    shell=True,
                    cwd=workdir,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE,
                )
                gcda_cov_dict = self._parse_gcov(output.stdout)
                for file, cov in gcda_cov_dict.items():
                    if not _in_exclude(file):
                        result_cov_dict[file] = cov
            for src_file in result_cov_dict:
                line_cnt += result_cov_dict[src_file]["line"]
                br_cnt += result_cov_dict[src_file]["branch"]
                line_all += result_cov_dict[src_file]["line_all"]
                br_all += result_cov_dict[src_file]["branch_all"]
            result_cov_dict["Summary"] = {
                "line": line_cnt,
                "branch": br_cnt,
                "line_all": line_all,
                "branch_all": br_all,
            }
            gcov_path = workdir / f"gcov-{_time}.json"
            gcov_path.write_text(json.dumps(result_cov_dict, indent=2))


def cov_to_csv(project: str, version: str):
    """
    Read produced coverage JSON, and make a summary csv file.

    :param project: The name of the project
    :param version: The version of the project
    """
    gcov_path = Path(project) / version / "gcov"
    csv_path = Path(project) / version / "gcov" / "coverage.csv"

    cov_data: dict[str, dict[int, tuple[int, int]]] = {}
    # {"promefuzz": {1: (line, branch), 2: (line, branch)}}
    for dir in gcov_path.iterdir():
        if dir.is_dir():
            run_id = dir.name.split("_")[0]
            run_time = dir.name.split("_")[-1]

            json_file = dir / f"gcov-24.json"
            if not json_file.exists():
                continue
            with open(json_file, "r") as f:
                data = json.load(f)
                line = data["Summary"]["line"]
                branch = data["Summary"]["branch"]
                if run_id not in cov_data:
                    cov_data[run_id] = {}
                cov_data[run_id][int(run_time)] = (line, branch)

    with open(csv_path, "w", newline="") as csvfile:
        csvwriter = csv.writer(csvfile)
        for run_id, run_dict in cov_data.items():
            # First row
            run_times = sorted(run_dict.keys())
            run_row = [run_id]
            for time in run_times:
                run_row.append(f"run {time}")
            # fill till 10
            if len(run_row) < 11:
                run_row.extend(["no run"] * (11 - len(run_row)))
            run_row.append("average")
            csvwriter.writerow(run_row)

            # line cov row
            line_row = ["line"]
            line_sum = 0
            for time in run_times:
                line_row.append(run_dict[time][0])
                line_sum += run_dict[time][0]
            if len(line_row) < 11:
                line_row.extend([" "] * (11 - len(line_row)))
            line_row.append(line_sum // len(run_times) if run_times else 0)
            csvwriter.writerow(line_row)

            # branch cov row
            branch_row = ["branch"]
            branch_sum = 0
            for time in run_times:
                branch_row.append(run_dict[time][1])
                branch_sum += run_dict[time][1]
            if len(branch_row) < 11:
                branch_row.extend([" "] * (11 - len(branch_row)))
            branch_row.append(branch_sum // len(run_times) if run_times else 0)
            csvwriter.writerow(branch_row)

    with open(csv_path, "r") as csvfile:
        logger.info(f"Coverage summary:\n{csvfile.read()}")

@click.command(help="Run GCov to get coverage information")
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
    "--is-header-lib",
    "-ih",
    "is_header_lib",
    is_flag=True,
    default=False,
    help="Whether the fuzz target is a header library",
)
@click.option(
    "--exclude-src",
    "-es",
    "exclude_src",
    help="The source paths to exclude from the coverage report",
    multiple=True,
    default=[],
)
@click.option(
    "--pool-size",
    "-ps",
    "pool_size",
    default=1,
    help="The pool size for the parallel execution",
)
def collect_gcov(
    config: Path,
    project: str,
    version: str,
    fuzz_id: str,
    is_header_lib: bool,
    exclude_src: list[str],
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

    gcov_path = Path(project) / version / "gcov"
    gcov_path.mkdir(parents=True, exist_ok=True)
    out_ids = [
        out_folder.name.removeprefix("out_")
        for out_folder in Path(config[project][version][fuzz_id]["out_base_path"]).glob(
            f"out_{fuzz_id}_*"
        )
    ]
    gcov = GCov(config)
    for out_id in tqdm.tqdm(
        out_ids, desc="Processing fuzzing results", unit="instance", leave=False
    ):
        gcov.run(
            project,
            version,
            fuzz_id,
            out_id,
            is_header_lib=is_header_lib,
            exclude_src=exclude_src,
            pool_size=pool_size,
        )
    cov_to_csv(project, version)

if __name__ == "__main__":
    collect_gcov()
