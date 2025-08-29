#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Run fuzzing with fuzz config.
"""
import libtmux
import tomllib
from libtmux.constants import PaneDirection
from abc import ABC, abstractmethod
from loguru import logger
from pathlib import Path
import click


class BaseFuzzer(ABC):

    # The name of the fuzzer, should be specified in the subclass
    fuzzer_name = ""

    def __init__(self, session: libtmux.Session, fuzz_config: dict):
        """
        Initialize a Fuzzer.

        :param session: tmux session to run the fuzzer.
        :param fuzz_config: Fuzz target configuration.
        """
        self.session = session
        self.fuzz_config = fuzz_config
        self.fuzzer_path = fuzz_config[self.fuzzer_name]["fuzzer_path"]

    @classmethod
    def from_config(cls, fuzz_config_path: Path):
        """
        Initialize a Fuzzer from a "fuzz.toml" configuration file.

        :param fuzz_config_path: Path to the "fuzz.toml" configuration file.
        """
        # create a tmux session for the fuzzer
        session_name = f"fuzz-{cls.fuzzer_name}"
        server = libtmux.Server()
        session = None
        try:
            session = server.sessions.get(session_name=session_name)
        except:
            session = server.new_session(session_name=session_name)

        fuzz_config = tomllib.loads(fuzz_config_path.read_text())
        return cls(session, fuzz_config)

    def _create_window(self, name="") -> libtmux.Window:
        """
        Create a new tmux window and split it into 4 panes

        :param name: Name of the window
        :return: The created window
        """
        window = self.session.new_window(name)
        window.split(direction=PaneDirection.Below, attach=True)
        window.split(direction=PaneDirection.Right)
        top_left_pane = window.panes[0]
        top_left_pane.split(direction=PaneDirection.Right)
        return window

    def _check_outdir(self, path_base: Path, fuzz_id, timeout) -> int:
        """
        Check the existing fuzz output, return next start_idx for fuzz

        :param path_base: The base path for the output
        :param fuzz_id: The fuzz id
        :return: The next start_idx
        """
        for i in range(0, 10):
            path_out = path_base / f"out_{fuzz_id}_{timeout}_{i}"
            if not path_out.exists():
                break
        else:
            i = -1
        return i

    @abstractmethod
    def fuzz(self, project_name: str, version: str, fuzz_id: str): ...


class AFLPPFuzzer(BaseFuzzer):

    # The name of the fuzzer
    fuzzer_name = "aflpp"

    def fuzz(self, project_name, version, fuzz_id, timeout=24):
        """
        Start fuzzing with AFL++

        :param project_name: The name of the project, e.g., ngiflib
        :param version: The version of the project, e.g., latest
        :param fuzz_id: The identification name of the fuzz target, e.g., promefuzz
        :param timeout: The duration of the fuzzing in hours.
        """

        FUZZ_CMD = "{FUZZER_PATH} -i {IN_PATH} -o {OUT_PATH} {AFLPP_ARGS} -- {DRIVER_PATH} {CMD}"
        try:
            fuzz_config = self.fuzz_config[project_name][version][fuzz_id]
        except:
            logger.error(f"{project_name}.{version}.{fuzz_id} not in fuzz config")
            return

        window = self._create_window(f"{project_name}:{version}:{fuzz_id}")
        path_base = Path(fuzz_config["out_base_path"])
        start_idx = self._check_outdir(path_base, fuzz_id, timeout)
        if start_idx == -1:
            print("Already fuzzed for 10 times")
            return
        logger.info(
            f"Fuzzing results will be saved to {path_base}/out_{fuzz_id}_{timeout}_{start_idx}~{start_idx + 3}"
        )

        in_path = Path(fuzz_config["in_path"])
        driver_path = Path(fuzz_config["bin"])

        for i in range(4):
            if start_idx + i >= 10:
                return
            work_path = path_base / f"out_{fuzz_id}_{timeout}_{start_idx + i}"
            work_path.mkdir(parents=True, exist_ok=True)
            out_path = work_path / "out"
            fuzz_cmd = FUZZ_CMD.format(
                FUZZER_PATH=self.fuzzer_path,
                IN_PATH=in_path.resolve(strict=True),
                OUT_PATH=out_path.resolve(),
                AFLPP_ARGS=fuzz_config["aflpp_args"] if "aflpp_args" in fuzz_config else "",
                DRIVER_PATH=driver_path.resolve(),
                CMD=fuzz_config["cmd"],
            )
            cmd_timeout = f"timeout -s 1 {timeout * 3600}"
            cmd = f"ASAN_OPTIONS='abort_on_error=1:symbolize=0:detect_odr_violation=0:allocator_may_return_null=1' {cmd_timeout} {fuzz_cmd}"
            # To deal with dummy_file, we run fuzz in the workdir
            window.panes[i].send_keys(f"cd {work_path}")
            window.panes[i].send_keys(cmd)


@click.command(help="Run fuzzing")
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
def fuzz(
    config: Path,
    project: str,
    version: str,
    fuzz_id: str,
):
    fuzzer = AFLPPFuzzer.from_config(config)
    fuzzer.fuzz(project, version, fuzz_id)
    logger.success("Fuzzing started, run `tmux a -t fuzz-aflpp` to see the progress")


if __name__ == "__main__":
    fuzz()
