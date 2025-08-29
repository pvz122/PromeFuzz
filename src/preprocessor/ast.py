"""
Run AST based preprocessor to extract metadata from the source code.
"""

from pathlib import Path
from loguru import logger
from multiprocessing import cpu_count
from concurrent.futures import ThreadPoolExecutor
import subprocess
from tqdm import tqdm
from abc import ABC, abstractmethod
import json
import tempfile
import shutil

import src.vars as global_vars
from src.utils import path_in_paths, with_progress_update
from processor.rust.rust import RustParser
from .meta import Meta


class ASTPreprocessor(ABC):
    """
    AST based preprocessor runner
    """

    POOL_SIZE = cpu_count()

    LANG_SUFFIX_MAP = {
        global_vars.SupportedLanguages.C: [".c", ".cpp", ".cc", ".cxx", ".c++"],
        global_vars.SupportedLanguages.CPP: [".c", ".cpp", ".cc", ".cxx", ".c++"],
        global_vars.SupportedLanguages.RUST: [".rs"],
    }

    def __init__(self):
        """
        Initialize the AST preprocessor, implemented by the subclass.
        The subclass should set self.source_files in the __init__ method.
        """
        self.source_files = []
        ...

    @classmethod
    @abstractmethod
    def from_library_config(cls, library_config: dict) -> "ASTPreprocessor":
        """
        Initialize the AST preprocessor from the library configuration.

        :param library_config: The library configuration.
        :return: The AST preprocessor.
        """
        ...

    def _get_source_files_from_source_paths(
        self, source_paths: list[Path]
    ) -> list[Path]:
        """
        Get the source files from the source paths.

        :param source_paths: The paths to the source code.
        :return: The source files.
        """
        SOURCE_SUFFIX = self.LANG_SUFFIX_MAP.get(global_vars.library_language)
        exclude_paths = [Path(_) for _ in global_vars.library_config["exclude_paths"]]
        source_files: list[Path] = []

        for source_path in source_paths:
            if source_path.is_file():
                source_files.append(source_path)
            elif source_path.is_dir():
                for suffix in SOURCE_SUFFIX:
                    source_files += list(source_path.rglob(f"*{suffix}"))
            else:
                logger.warning(f"Invalid source path {source_path}")

        # filter out the exclude paths
        source_files = [
            file.resolve()
            for file in source_files
            if not path_in_paths(file, exclude_paths)
        ]

        logger.debug(
            f"Found {len(source_files)} source files in source paths:\n{'\n'.join([str(file) for file in source_files])}"
        )

        return source_files

    @abstractmethod
    def run_once(self, source_file: Path) -> Meta:
        """
        Run the AST preprocessor for one source file.

        :param source_file: The source file.
        """
        pass

    def run(self) -> Meta:
        """
        Run the AST preprocessor.

        :return: The merged results.
        """
        logger.info(
            f"Running AST Preprocessor for all {len(self.source_files)} source files."
        )
        self.progress_bar = tqdm(
            total=len(self.source_files),
            desc="Running AST Preprocessor",
            unit="source files",
            colour="YELLOW",
            leave=False,
        )

        run_once_with_progress = with_progress_update(self.run_once)
        if self.POOL_SIZE > 1:
            # run the preprocessor for all source files in parallel
            with ThreadPoolExecutor(max_workers=self.POOL_SIZE) as pool:
                results = pool.map(
                    lambda source_file: run_once_with_progress(
                        source_file, progress=self.progress_bar
                    ),
                    self.source_files,
                )
        else:
            # run the preprocessor in serial, useful for debugging
            results = []
            for source_file in self.source_files:
                results.append(
                    run_once_with_progress(source_file, progress=self.progress_bar)
                )

        # merge the results
        meta = Meta.merge(results)

        self.progress_bar.close()
        logger.success(f"Preprocessed {len(self.source_files)} source files.")
        return meta


class CXXASTPreprocessor(ASTPreprocessor):
    """
    Class for running the Clang-based AST preprocessor for C/C++.
    """

    PROCESSOR_BIN: Path = None

    def __init__(self, source_paths: list[Path], compile_commands_path: Path | None):
        """
        Initialize the CXX AST preprocessor.

        :param source_paths: The paths to the source code.
        :param compile_commands_path: The path to the compile_commands.json.
        """
        self.compile_commands_path = compile_commands_path

        # get the source files
        self.source_files = list(
            set(self._get_source_files_from_compile_commands(compile_commands_path))
            | set(self._get_source_files_from_source_paths(source_paths))
        )

    @classmethod
    def from_library_config(cls, library_config: dict) -> "CXXASTPreprocessor":
        """
        Initialize the AST preprocessor from the library configuration.

        :param library_config: The library configuration.
        :return: The AST preprocessor.
        """
        source_paths = [Path(_) for _ in library_config["source_paths"]]
        if library_config["compile_commands_path"]:
            return cls(source_paths, Path(library_config["compile_commands_path"]))
        else:
            logger.warning(
                "compile_commands_path is not set in the library configuration, the AST preprocessor may not work."
            )
            return cls(source_paths, None)

    def _get_source_files_from_compile_commands(
        self, compile_commands_path: Path
    ) -> list[Path]:
        """
        Get the source files from the compile_commands.json.

        :param compile_commands_path: The path to the compile_commands.json.
        :return: The source files.
        """
        if compile_commands_path is None:
            return []

        try:
            cc = json.loads(compile_commands_path.read_text())
        except Exception as e:
            raise Exception(
                f"Failed to load compile_commands.json from {compile_commands_path}: {e}"
            )

        source_files: list[Path] = []
        for entry in cc:
            f = Path(entry["file"])
            if not f.is_absolute():
                f = Path(entry["directory"]) / f
            f = f.resolve()
            if f.is_file():
                source_files.append(f)
            else:
                logger.warning(f"Invalid source file {f} in compile_commands.json")

        logger.debug(
            f"Found {len(source_files)} source files in compile_commands.json:\n{'\n'.join([str(file) for file in source_files])}"
        )

        return source_files

    def run_once(self, source_file):
        """
        Run the CXX AST preprocessor for one source file.

        :param source_file: The source file.
        """
        with tempfile.TemporaryDirectory(
            dir=(
                "/dev/shm"
                if (
                    Path("/dev/shm").exists()
                    and shutil.disk_usage("/dev/shm").free >= 1073741824
                )
                else None
            )
        ) as tmp_dir:
            meta_file = Path(tmp_dir) / "meta.json"

            cmd = f"{self.PROCESSOR_BIN} {source_file} -o {meta_file}" + (
                f" -p {self.compile_commands_path.resolve().parent}"
                if self.compile_commands_path
                else ""
            )
            logger.debug(f"Running CXX AST preprocessor for {source_file}: \n{cmd}")
            result = subprocess.run(
                cmd,
                shell=True,
                capture_output=True,
                text=True,
                errors="replace",
            )

            output = result.stdout + result.stderr
            if output:
                logger.warning(
                    f"AST preprocessor warning/error for {source_file}: \n{output}"
                )

            if result.returncode != 0:
                logger.error(
                    f"Failed to run CXX AST preprocessor for {source_file}: \n{cmd}\nerror: \n{result.stderr}"
                )
                return Meta({})

            try:
                return Meta.load(meta_file)
            except ValueError as e:
                logger.error(
                    f"Failed to load meta data for {source_file}: {e}, AST preprocessor may failed."
                )
                return Meta({})


class RustASTPreprocessor(ASTPreprocessor):
    """
    Class for running the tree-sitter based AST preprocessor for Rust.
    TODO: This class is not well implemented yet.
    """

    def __init__(self, source_paths: list[Path]):
        """
        Initialize the Rust AST preprocessor.

        :param source_paths: The paths to the source code.
        """
        self.source_files = self._get_source_files_from_source_paths(source_paths)

    @classmethod
    def from_library_config(cls, library_config: dict) -> "RustASTPreprocessor":
        """
        Initialize the AST preprocessor from the library configuration.

        :param library_config: The library configuration.
        :return: The AST preprocessor.
        """
        source_paths = [Path(_) for _ in library_config["source_paths"]]
        return cls(source_paths)

    def run_once(self, source_file):
        """
        Run the Rust AST preprocessor for one source file.

        :param source_file: The source file.
        """
        parser = RustParser(source_file)
        try:
            parser.parse()
        except Exception as e:
            logger.error(
                f"Failed to run Rust AST preprocessor for {source_file}: \nerror: \n{e}"
            )
            return Meta({})
        else:
            return Meta(parser.get())
