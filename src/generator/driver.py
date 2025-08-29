"""
Fuzz Driver
"""

import threading
from pathlib import Path
from loguru import logger
import subprocess
import json
from typing import Callable

from src import vars as global_vars
from src.llm.llm import LLMChat
from src.preprocessor.api import APIFunction, APICollection


class FuzzDriver:
    """
    Class to store the fuzz driver
    """

    # config constants
    MAX_SAN_ROUNDS = 5
    PROCESSOR_BIN: Path = None
    USE_POSTPROCESSOR = True
    CLEANUP_POST = False

    # lock for generating new id
    lock = threading.Lock()
    gen_count = 0

    def __init__(
        self,
        fuzz_driver_code: str,
        llm_chat: LLMChat,
        target_functions,
    ):
        """
        Initialize the fuzz driver

        :param fuzz_driver_code: The fuzz driver source code
        :param llm_chat: The LLM chat with the fuzz driver is associated
        :param target_functions: The target functions to be fuzzed, can be either a FunctionSet or an OrderSet
        """
        # import here to avoid circular import
        from .scheduler import FunctionSet
        from src.preprocessor.consumer import OrderSet

        self.fuzz_driver_code = fuzz_driver_code
        self.llm_chat = llm_chat

        # target_functions is either a FunctionSet or an OrderSet; function_set is always a FunctionSet
        self.target_functions: FunctionSet | OrderSet = target_functions
        self.function_set: FunctionSet = (
            target_functions.as_function_set
            if isinstance(target_functions, OrderSet)
            else target_functions
        )

        self.id = self._new_id()
        self.remain_san_rounds = self.MAX_SAN_ROUNDS  # remaining sanitization rounds
        self.sanitized = False  # whether the fuzz driver has been sanitized
        self.query_count = 0  # the number of queries sent to generate the fuzz driver

    @staticmethod
    def _new_id() -> int:
        """
        Generate a new id

        :return: The new id
        """
        with FuzzDriver.lock:
            FuzzDriver.gen_count += 1
            new_id = FuzzDriver.gen_count
        return new_id

    @property
    def build_cmd(self) -> str:
        """
        The build command for the fuzz driver

        :return: A format string with placeholders: compiler, source, dest
        """
        # get all header paths in target functions
        header_paths = set(
            Path(p).resolve().parent for p in self.function_set.header_paths
        )
        header_paths.update(
            Path(header).resolve().parent
            for header in global_vars.library_config["driver_headers"]
        )

        # get build args
        build_args = global_vars.library_config["driver_build_args"]

        # construct build command
        return (
            "{compiler}"
            + " {source} -o {dest} -fsanitize=fuzzer,address,undefined -g "
            + " ".join([f"-I{p}" for p in header_paths])
            + " "
            + " ".join(build_args)
        )

    def save(
        self,
        dest_path: Path,
        filename: str = "default",
        save_build_script: bool = False,
        add_comment: str = "",
    ):
        """
        Save the fuzz driver to file

        :param dest_path: The destination directory where the fuzz driver will be saved
        :param filename: The filename of the fuzz driver, default to 'fuzz_driver_{id}.cpp'
        :param save_build_script: Whether to save the build script along with the fuzz driver
        :param add_comment: Additional comment to be added to the top of the file
        """
        # If fuzz driver code is empty, raise error
        if not self.fuzz_driver_code:
            raise ValueError("Fuzz driver code is empty, cannot save to file")

        # prepare file names
        suffix = (
            ".cpp"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else ".c"
        )
        filename = (
            filename if filename != "default" else f"fuzz_driver_{self.id}{suffix}"
        )
        binname = filename.removesuffix(suffix)
        script_filename = f"build_{binname}.sh"
        src_file = dest_path / filename

        # save fuzz driver
        comments = (
            ("".join(f"// {_}\n" for _ in add_comment.split("\n")))
            if add_comment
            else ""
        )
        src_file.write_text(comments + self.fuzz_driver_code)
        logger.debug(f"Fuzz driver {self.id} saved to {str(src_file)}")

        # create "./dummy_file" if fuzz driver uses dummy file
        if "dummy_file" in self.fuzz_driver_code:
            dummy_file = dest_path / "dummy_file"
            if not dummy_file.exists():
                dummy_file.touch()

        # save build script
        if save_build_script:
            # XXX: the paths in build args are relative to promefuzz,
            # we use "cd promefuzz" to find the correct paths in build args
            build_script = """#! /bin/bash\n
cd {promefuzz_path}
{build_cmd}
""".format(
                promefuzz_path=str(global_vars.promefuzz_path),
                build_cmd=self.build_cmd.format(
                    compiler=(
                        "clang++"
                        if global_vars.library_language
                        == global_vars.SupportedLanguages.CPP
                        else "clang"
                    ),
                    source=(dest_path / filename),
                    dest=(dest_path / binname),
                ),
            )
            build_script_path = Path(dest_path) / script_filename
            build_script_path.write_text(build_script)
            build_script_path.chmod(0o755)
            logger.debug(
                f"Build script for fuzz driver {self.id} saved to {str(build_script_path)}"
            )

    def build(
        self,
        dest_path: Path = Path("/tmp"),
        filename: str = "default",
        extra_build_args: list = [],
        cleanup: bool = True,
    ) -> tuple[bool, str]:
        """
        Build the fuzz driver

        :param dest_path: The destination directory where the built fuzz driver will be saved, default to /tmp
        :param filename: The filename of the built fuzz driver, default to 'fuzz_driver_{id}'
        :param extra_build_args: Extra arguments for compiler
        :param cleanup: Whether to cleanup the built files after building
        :return: a tuple of (success, output)
        """
        # If fuzz driver code is empty, raise error
        if not self.fuzz_driver_code:
            raise ValueError("Fuzz driver code is empty, cannot build")

        # prepare file names
        suffix = (
            ".cpp"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else ".c"
        )
        filename = (
            filename if filename != "default" else f"fuzz_driver_{self.id}{suffix}"
        )
        binname = filename.removesuffix(suffix)
        src_path = dest_path / filename
        bin_path = dest_path / binname

        def _cleanup():
            if cleanup:
                src_path.unlink(missing_ok=True)
                bin_path.unlink(missing_ok=True)

        # save fuzz driver
        try:
            self.save(dest_path, filename)
        except Exception as e:
            _cleanup()
            raise e

        # prepare build command
        compiler = (
            "clang++"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else "clang"
        )
        build_cmd = (
            self.build_cmd.format(compiler=compiler, source=src_path, dest=bin_path)
            + " "
            + " ".join(extra_build_args)
        )
        logger.debug(f"Building fuzz driver {self.id} with command: {build_cmd}")

        # build fuzz driver
        try:
            output = subprocess.check_output(
                build_cmd, stderr=subprocess.STDOUT, shell=True, text=True
            )
            logger.debug(f"Build output: {output}")
        except subprocess.CalledProcessError as e:
            _cleanup()
            return False, e.output
        except Exception as e:
            _cleanup()
            raise e

        _cleanup()
        return True, output

    def run(
        self,
        timeout: int = -1,
        dest_path: Path = Path("/tmp"),
        filename: str = "default",
        extra_build_args: list = [],
        extra_run_args: list = [],
        cleanup: bool = True,
    ) -> tuple[str, str]:
        """
        Run the fuzz driver

        :param timeout: The timeout for running the fuzz driver. After the timeout, the process will be
                        terminated. If set to -1, the process will run indefinitely. Default to -1.
        :param dest_path: The destination directory where the built fuzz driver will be saved.
                          If not provided, the driver will be saved to /tmp and removed after the run.
        :param filename: The filename of the built fuzz driver, default to 'fuzz_driver_{id}'
        :param extra_build_args: Extra arguments for compiler
        :param extra_run_args: Extra arguments for running the fuzz driver
        :param cleanup: Whether to cleanup the built files after building
        :return: a tuple of (status, output). Status is one of the following:
                    - "OK": the fuzz driver ran successfully and terminated after timeout
                    - "BUILDFAIL": the fuzz driver failed to build
                    - "CRASH": the fuzz driver crashed during execution
        """
        # get file names
        suffix = (
            ".cpp"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else ".c"
        )
        filename = (
            filename if filename != "default" else f"fuzz_driver_{self.id}{suffix}"
        )
        binname = filename.removesuffix(suffix)
        src_path = dest_path / filename
        bin_path = dest_path / binname

        def _cleanup():
            if cleanup:
                src_path.unlink(missing_ok=True)
                bin_path.unlink(missing_ok=True)

        # build fuzz driver
        build_result, build_output = self.build(
            dest_path, filename, extra_build_args, False
        )
        if not build_result:
            _cleanup()
            return "BUILDFAIL", build_output

        # run fuzz driver
        run_cmd = f"{str(bin_path)} {' '.join(extra_run_args)}"
        logger.debug(f"Running fuzz driver {self.id} with command: {run_cmd}")
        try:
            output = subprocess.run(
                run_cmd,
                timeout=None if timeout < 0 else timeout,
                cwd=str(dest_path),
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                shell=True,
                text=True,
                errors="replace",
                check=True,
            ).stdout
            logger.debug(f"Run output: {output}")
        except subprocess.TimeoutExpired as e:
            _cleanup()
            return "OK", e.output
        except subprocess.CalledProcessError as e:
            _cleanup()
            return "CRASH", e.output
        except Exception as e:
            _cleanup()
            raise e

        # cannot reach here normally, but extra_run_args may cause this
        _cleanup()
        return "OK", output

    @property
    def check_actual_targets(
        self,
    ) -> Callable[[APICollection], tuple[list[APIFunction], list[APIFunction]]]:
        """
        The function to check the actually called target functions of the fuzz driver
        """
        return (
            self.check_actual_targets_ast
            if self.USE_POSTPROCESSOR
            else self.check_actual_targets_naive
        )

    def check_actual_targets_naive(
        self,
        _=None,
    ) -> tuple[list[APIFunction], list[APIFunction]]:
        """
        Check the actually called target functions of the fuzz driver using string matching

        :param _: Placeholder
        :return: A tuple of two lists: (actual_targets, missing_targets)
        """
        actual_targets = []
        missing_targets = []
        for func in self.function_set.safe_iter:
            if f"{func.name.split("::")[-1]}(" in self.fuzz_driver_code:
                actual_targets.append(func)
            else:
                missing_targets.append(func)

        return actual_targets, missing_targets

    def check_actual_targets_ast(
        self,
        api_collection: APICollection,
    ) -> tuple[list[APIFunction], list[APIFunction]]:
        """
        Check the actually called target functions of the fuzz driver using AST post-processing

        :param api_collection: The API functions collection
        :return: A tuple of two lists: (actual_targets, missing_targets)
        """
        # save the fuzz driver
        save_name = f"postprocessing_{self.id}." + (
            "cpp"
            if global_vars.library_language == global_vars.SupportedLanguages.CPP
            else "c"
        )
        tmp_path = (
            Path(global_vars.library_config["output_path"]) / "tmp" / "postprocessing"
        )
        tmp_path.mkdir(parents=True, exist_ok=True)
        save_path = tmp_path / save_name
        output_path = tmp_path / f"{save_name}.json"
        self.save(tmp_path, save_name)

        def _cleanup():
            if self.CLEANUP_POST:
                save_path.unlink(missing_ok=True)
                output_path.unlink(missing_ok=True)

        # run the CGprocessor for the fuzz driver
        cmd = self.build_cmd.format(
            compiler=self.PROCESSOR_BIN,
            source=save_path,
            dest=f"{output_path} --",
        )
        logger.debug(
            f"Running CGprocessor for fuzz driver {self.id} with command:\n {cmd}"
        )
        try:
            output = subprocess.check_output(
                cmd, stderr=subprocess.STDOUT, shell=True, text=True
            )
            logger.debug(f"CGprocessor output: {output}")
        except subprocess.CalledProcessError as e:
            logger.error(f"CGprocessor failed for fuzz driver {self.id}: {e.output}")
            _cleanup()
            return [], [self.function_set.safe_iter]

        # load the CGprocessor output
        try:
            calling_info: dict[str, dict[str, str]] = json.loads(
                output_path.read_text()
            )
        except Exception as e:
            logger.error(
                f"Failed to load CGprocessor output for fuzz driver {self.id}: {e}"
            )
            _cleanup()
            return [], [self.function_set.safe_iter]

        # check the actual targets
        actual_targets = []
        for _, calling in calling_info.items():
            target = api_collection.get_by_decl_location(calling["calleeDeclLoc"])
            if target:
                actual_targets.append(target)
            else:
                # dismiss operators
                if "operator" not in calling["calleeName"]:
                    logger.warning(
                        f"Function in fuzz driver does not exist in API collection: {calling["calleeName"]} at {calling["calleeDeclLoc"]}"
                    )
        missing_targets = [
            func for func in self.function_set.safe_iter if func not in actual_targets
        ]

        _cleanup()
        return actual_targets, missing_targets
