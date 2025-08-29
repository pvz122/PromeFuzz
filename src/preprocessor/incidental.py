"""
Get the incidental relations of the API functions.
If the API function A calls API function B, then B is incidental to A.
Any invocation of A will be considered as a potential invocation of B.
"""

from loguru import logger
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import cpu_count
from functools import cached_property
from tqdm import tqdm
import subprocess
import tempfile
import shutil
import json
import pickle

from .ast import CXXASTPreprocessor
from .api import APICollection, APIFunction
from .consumer import CallGraph


class Incidentals:
    """
    Class to store the incidental relations of the API functions.
    """

    def __init__(self, api_collection: APICollection):
        """
        Initialize the Incidentals

        :param api_collection: The API functions collection
        """
        self.incidentals: dict[APIFunction, set[APIFunction]] = {
            api: set() for api in api_collection.safe_iter
        }

    def add(self, api: APIFunction, incidental: APIFunction):
        """
        Add an incidental relation

        :param api: The API function
        :param incidental: The incidental API function
        """
        self.incidentals[api].add(incidental)

    def get(self, api: APIFunction) -> list[APIFunction]:
        """
        Get the incidentals of an API function

        :param api: The API function
        :return: The list of incidental API functions
        """
        return list(self.incidentals[api])

    def is_incidental(self, api: APIFunction, incidental: APIFunction) -> bool:
        """
        Check if an API function is incidental to another API function

        :param api: The API function
        :param incidental: The incidental API function
        :return: True if incidental, False otherwise
        """
        return incidental in self.incidentals[api]

    def dump(self, file: Path):
        """
        Dump the Incidentals to a file

        :param file: The file to dump the Incidentals
        """
        with open(file, "wb") as f:
            pickle.dump(self.incidentals, f)

    @classmethod
    def load(cls, file: Path) -> "Incidentals":
        """
        Load the Incidentals from a file

        :param file: The file to load the Incidentals
        :return: The loaded Incidentals
        """
        incidentals = cls.__new__(cls)
        with open(file, "rb") as f:
            incidentals.incidentals = pickle.load(f)
        return incidentals

    def dump_json(self, file: Path):
        """
        Dump the Incidentals to a JSON file, only for human-readable

        :param file: The file to dump the Incidentals
        """
        with open(file, "w") as f:
            json.dump(
                {
                    str(api): [str(incidental) for incidental in incidentals]
                    for api, incidentals in self.incidentals.items()
                },
                f,
                indent=4,
            )


class IncidentalsExtractor:
    """
    Class for extracting the incidental relations of the API functions.
    """

    def __init__(self, call_graph: CallGraph):
        """
        Initialize the Incidentals Extractor

        :param call_graph: The library source Call Graph
        """
        self.call_graph = call_graph

    def extract(self) -> Incidentals:
        """
        Extracts the incidental relations from the Call Graph.

        :return: Incidentals
        """
        # Algorithm:
        # for each api_nodes in the call_graph:
        #   traverse the call graph (directed graph) from the api_node, and get all the nodes reachable from it
        #   if the reachable node is an API node, then add it to the incidentals of the api_node
        incidentals = Incidentals(self.call_graph.api_collection)

        for api_node in self.call_graph.api_nodes:
            # for reachable_node in self.call_graph.reachable_nodes(api_node):
            # XXX: since some of the reachable nodes are too deep, we only traverse one level
            for reachable_node in api_node.callee:
                if reachable_node.api is not None:
                    incidentals.add(api_node.api, reachable_node.api)

        return incidentals


class LibraryCallGraphBuilder:
    """
    Class for building Call Graph from library source code.
    """

    # The path to the CGprocessor binary
    PROCESSOR_BIN: Path = None
    # The pool size
    POOL_SIZE: int = cpu_count()

    def __init__(
        self,
        source_files: list[Path],
        compile_commands_path: Path | None,
        api_collection: APICollection,
    ):
        """
        Initialize the Call Graph Builder

        :param source_files: The list of source files
        :param compile_commands_path: The path to the compile_commands.json file
        :param api_collection: The API functions collection
        """
        self.source_files = source_files
        self.compile_commands_path = compile_commands_path
        self.api_collection = api_collection

    @classmethod
    def from_ast_preprocessor(
        cls, ast_preprocessor: CXXASTPreprocessor, api_collection: APICollection
    ) -> "LibraryCallGraphBuilder":
        """
        Initialize the Call Graph Builder from the AST Preprocessor

        :param ast_preprocessor: The AST Preprocessor
        :param api_collection: The API functions collection
        """
        return cls(
            ast_preprocessor.source_files,
            ast_preprocessor.compile_commands_path,
            api_collection,
        )

    def build_graph(self) -> CallGraph:
        """
        Build the Call Graph from the source

        :return: The Call Graph
        """
        call_graph = CallGraph(self.api_collection)

        for (
            caller_name,
            caller_location,
            callee_name,
            callee_location,
        ) in self.calling_pairs:
            call_graph.add_call(
                caller_name, caller_location, callee_name, callee_location
            )

        return call_graph

    @cached_property
    def calling_pairs(self) -> list[tuple[str, str, str, str]]:
        """
        Process the source files and get the caller-callee pairs

        :return: The list of position-caller-callee pairs, like (caller_name, caller_location, callee_name, callee_location)
        """
        pairs = []

        progress_bar = tqdm(
            total=len(self.source_files),
            desc="Running AST CallGraph Processor for library source code",
            unit="file",
            leave=False,
            colour="YELLOW",
        )

        def _process_one_source_with_progress(source_file: Path):
            result = self._process_one_source(source_file)
            progress_bar.update(1)
            return result

        if self.POOL_SIZE == 1:
            for source_file in self.source_files:
                pairs += _process_one_source_with_progress(source_file)
        else:
            with ThreadPoolExecutor(max_workers=self.POOL_SIZE) as executor:
                pairs = sum(
                    executor.map(_process_one_source_with_progress, self.source_files),
                    [],
                )

        return pairs

    def _process_one_source(self, source_file: Path) -> list[tuple[str, str, str, str]]:
        """
        Process one source file and get the caller-callee pairs

        :param source_file: The source file to process
        :return: The list of caller-callee pairs, like (caller_name, caller_location, callee_name, callee_location)
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
            # run the CGprocessor binary
            cg_file = Path(tmp_dir) / "cg.json"
            cmd = f"{self.PROCESSOR_BIN} {source_file} -o {cg_file}" + (
                f" -p {self.compile_commands_path.resolve().parent}"
                if self.compile_commands_path
                else ""
            )
            logger.debug(f"Running CGprocessor for source {source_file}: \n{cmd}")
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
                    f"CGprocessor warning/error for source {source_file}:\n{output}"
                )
            if result.returncode != 0:
                logger.error(
                    f"Failed to run CGprocessor for source {source_file}: \n{cmd}\nerror: \n{result.stderr}"
                )
                return []

            # load the cg.json file
            try:
                with open(cg_file, "r") as f:
                    cg = json.load(f)
            except Exception as e:
                logger.error(f"Failed to load cg.json from {cg_file}: {e}")
                return []

            pairs = []
            for _, calling_info in cg.items():
                pairs.append(
                    (
                        calling_info["callerName"],
                        calling_info["callerDeclLoc"],
                        calling_info["calleeName"],
                        calling_info["calleeDeclLoc"],
                    )
                )
            if not pairs:
                logger.warning(
                    f"No caller-callee pairs found for source {source_file}."
                )
            else:
                logger.debug(
                    f"Found {len(pairs)} caller-callee pairs for source {source_file}."
                )
            return pairs
