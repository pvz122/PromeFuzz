"""
Process consumer cases

DESIGN:
The whole concept here is library consumers(like UT) contain a lot of information
about how the API functions should be used. On the one hand, we can extract
the calling order of the APIs, and directly use them to generate the fuzz
driver. On the other hand, we can build a call graph from the consumer cases,
and use the call graph to evaluate the relevance of the API functions.

For calling order extraction, the process is:
1. Get all the API calling chains from the consumer cases. Only the direct calls are considered.
2. Since the calling chains may be too long or too short, we need to normalize them into
    a rather fixed size of OrderSet.
3. Since the number of calling chains may be huge, we need to minimize them using the Set Cover algorithm.

For call graph building, the process is:
1. Extract the caller-callee pairs from the consumer cases.
2. Build the call graph from the caller-callee pairs, on which every node is a function and
    every edge is a call relation.
3. Calculate the relevance of the API functions based on the shortest path length among them.
"""

from dataclasses import dataclass
from functools import cached_property, cache
from pathlib import Path
from loguru import logger
import pickle
import json
from concurrent.futures import ThreadPoolExecutor
from multiprocessing import cpu_count
import subprocess
import tempfile
import shutil
from tqdm import tqdm

from src.utils import path_in_paths, FilePos
from .api import APIFunction, APICollection


@dataclass
class CallGraphNode:
    """
    Class for a Call Graph Node
    """

    function_name: str
    """
    The function name
    """

    function_location: str
    """
    The function declaration location
    """

    caller: list["CallGraphNode"]
    """
    The list of functions that call this function
    """

    callee: list["CallGraphNode"]
    """
    The list of functions that this function calls
    """

    def __eq__(self, value):
        if isinstance(value, CallGraphNode):
            return self.function_location == value.function_location
        return False

    def __hash__(self):
        return hash(self.function_location)

    @classmethod
    def new_solitary_node(cls, function_name: str, function_location: str):
        """
        Create a CallGraphNode object with empty caller and callee

        :param function_name: The function name
        :param function_location: The function declaration location
        """
        return cls(function_name, function_location, [], [])

    @cached_property
    def api(self) -> APIFunction | None:
        """
        The APIFunction object of the function if it is an API function, otherwise None
        """
        api = CallGraph.api_collection.get_by_decl_location(self.function_location)
        if api is None:
            api = CallGraph.api_collection.get_by_location(self.function_location)
        return api

    def add_caller(self, caller: "CallGraphNode"):
        """
        Add a caller to the function

        :param caller: The caller function
        """
        if caller not in self.caller:
            self.caller.append(caller)

    def add_callee(self, callee: "CallGraphNode"):
        """
        Add a callee to the function

        :param callee: The callee function
        """
        if callee not in self.callee:
            self.callee.append(callee)


class CallGraph:
    """
    Class for Call Graph
    """

    api_collection: APICollection = None

    def __init__(self, api_collection: APICollection):
        """
        Initialize the Call Graph
        """
        CallGraph.api_collection = api_collection

        # The dictionary of call nodes, key is the function location
        self.call_nodes: dict[str, CallGraphNode] = {}
        # The list of API nodes
        self.api_nodes: list[CallGraphNode] = []

    def add_call(
        self,
        caller_name: str,
        caller_location: str,
        callee_name: str,
        callee_location: str,
    ):
        """
        Add a call from caller to callee

        :param caller_name: The caller function name
        :param caller_location: The caller function declaration location
        :param callee_name: The callee function name
        :param callee_location: The callee function declaration location
        """
        # create the caller and callee nodes or get them if they already exist
        if caller_location in self.call_nodes:
            caller = self.call_nodes[caller_location]
        else:
            caller = CallGraphNode.new_solitary_node(caller_name, caller_location)
            if caller.api is not None:
                self.api_nodes.append(caller)
        if callee_location in self.call_nodes:
            callee = self.call_nodes[callee_location]
        else:
            callee = CallGraphNode.new_solitary_node(callee_name, callee_location)
            if callee.api is not None:
                self.api_nodes.append(callee)

        # add the call
        caller.add_callee(callee)
        callee.add_caller(caller)

        # add to the call_nodes dictionary
        self.call_nodes[caller_location] = caller
        self.call_nodes[callee_location] = callee

    def traverse(self, start_node: CallGraphNode, is_directed_graph: bool = True):
        """
        Traverse the call graph from the start_node using BFS, emitting nodes and distance as a Generator.

        :param start_node: The node to start the traversal
        :param is_directed_graph: Whether the graph is directed. If False, the traversal will be undirected.
        :return: The Generator of nodes and distance
        """
        visited = set()
        queue = [(start_node, 0)]
        while queue:
            node, distance = queue.pop(0)
            if node in visited:
                continue
            visited.add(node)
            yield node, distance
            for callee in node.callee:
                queue.append((callee, distance + 1))
            if not is_directed_graph:
                for caller in node.caller:
                    queue.append((caller, distance + 1))

    @cache
    def reachable_nodes(
        self, start_node: CallGraphNode, is_directed_graph: bool = True
    ) -> list[CallGraphNode]:
        """
        Get the reachable nodes from the start_node using BFS

        :param start_node: The node to start the traversal
        :param is_directed_graph: Whether the graph is directed. If False, the traversal will be undirected.
        :return: The set of reachable nodes
        """
        return [node for node, _ in self.traverse(start_node, is_directed_graph)]

    def dump(self, path: Path):
        """
        Dump the Call Graph to a file

        :param path: The path to the file
        """
        with open(path, "wb") as f:
            pickle.dump(self.call_nodes, f)

    @classmethod
    def load(cls, path: Path, api_collection: APICollection) -> "CallGraph":
        """
        Load the Call Graph from a file

        :param path: The path to the file
        :param api_collection: The APICollection object
        """
        with open(path, "rb") as f:
            call_nodes = pickle.load(f)
        call_graph = cls(api_collection)
        call_graph.call_nodes = call_nodes
        for node in call_graph.call_nodes.values():
            if node.api is not None:
                call_graph.api_nodes.append(node)
        return call_graph

    def dump_json(self, path: Path):
        """
        Dump the Call Graph to a JSON file, only for human-readable, not for loading

        :param path: The path to the file
        """
        data = {
            f"{node.function_name}@{node.function_location}": {
                "caller": [
                    f"{caller.function_name}@{caller.function_location}"
                    for caller in node.caller
                ],
                "callee": [
                    f"{callee.function_name}@{callee.function_location}"
                    for callee in node.callee
                ],
            }
            for node in self.call_nodes.values()
        }
        with open(path, "w") as f:
            json.dump(data, f, indent=4)


class RawCallingOrder:
    """
    Class representing the raw calling order of API functions in the consumer.
    It is categorized as as: file -> caller -> list of (position, APIFunction)
    """

    def __init__(self):
        """
        Initialize an empty CallingOrder object

        :param calling_order: The calling order dictionary
        """
        self.calling_order: dict[str, dict[str, list[tuple[FilePos, APIFunction]]]] = {}

    def add_api_call(
        self,
        calling_pos: FilePos,
        caller_name: str,
        caller_location: str,
        api: APIFunction,
    ):
        """
        Add an API call to the calling order

        :param calling_pos: The position of the API call
        :param caller_name: The caller function name
        :param caller_location: The caller function declaration location
        :param api: The APIFunction object
        """
        caller_name = f"{caller_name}@{caller_location.split('/')[-1]}"
        calling_order_list = self.calling_order.setdefault(
            str(calling_pos.file), {}
        ).setdefault(caller_name, [])
        # insert it to the correct place
        for i, (pos, _) in enumerate(calling_order_list):
            if pos > calling_pos:
                insert_index = i
                break
        else:
            insert_index = len(calling_order_list)

        calling_order_list.insert(insert_index, (calling_pos, api))

    @property
    def iter_order_list(self):
        """
        Iterate over the API call order.
        Yields list of each API call in the order
        """
        for _, caller_dict in self.calling_order.items():
            for _, calling_order_list in caller_dict.items():
                yield [api for _, api in calling_order_list]

    def dump_json(self, path: Path):
        """
        Dump the calling order to a JSON file, only for human-readable

        :param path: The path to the file
        """
        with open(path, "w") as f:
            json.dump(
                {
                    file: {
                        caller: [
                            {
                                "pos": str(pos),
                                "api": str(api),
                            }
                            for pos, api in calling_order_list
                        ]
                        for caller, calling_order_list in caller_dict.items()
                    }
                    for file, caller_dict in self.calling_order.items()
                },
                f,
                indent=4,
                ensure_ascii=False,
            )


class OrderSet:
    """
    Class to present a set of API functions that are called in order.
    This set will be directly offered to the LLM to generate fuzz driver.
    """

    # The minimum and maximum size of the unique API functions in the set
    MIN_SIZE = 3
    MAX_SIZE = 10

    def __init__(self, normalized_order_list: list[APIFunction]):
        """
        Initialize the OrderSet

        :param normalized_order_list: The list of API functions in the order, size normalized
        """
        self.order_list = normalized_order_list

    @cached_property
    def unique_api_functions(self) -> set[APIFunction]:
        """
        The set of unique API functions in the order
        """
        return set(self.order_list)

    @cached_property
    def size(self) -> int:
        """
        The size of the unique API functions in the set
        """
        return len(self.unique_api_functions)

    @cached_property
    def as_function_set(self):
        """
        Get the OrderSet as a FunctionSet object, used for generation
        """
        # avoid circular import
        from src.generator.scheduler import FunctionSet

        return FunctionSet(list(self.unique_api_functions))

    @classmethod
    def from_order_list(cls, order_list: list[APIFunction]) -> list["OrderSet"]:
        """
        Generate a list of OrderSet objects from the order list

        :param order_list: The list of API functions in the order
        """
        new_order_set = cls(order_list)
        if new_order_set.size < cls.MIN_SIZE:
            # the order set is too small, return empty list
            return []
        elif new_order_set.size <= cls.MAX_SIZE:
            # the order set is within the size range, return it directly
            return [new_order_set]
        else:
            # split the order set into multiple order sets
            split_number = (
                (new_order_set.size // cls.MAX_SIZE)
                + (new_order_set.size // cls.MIN_SIZE)
            ) // 2  # split_number is the average of the number of splits based on MIN_SIZE and MAX_SIZE
            split_size = new_order_set.size // split_number
            split_result = []

            def _get_sub_order_list_of_size(size: int):
                cur_order_list = []
                cur_unique_api_functions = []
                for api in order_list:
                    cur_order_list.append(api)
                    if api not in cur_unique_api_functions:
                        cur_unique_api_functions.append(api)

                    if len(cur_unique_api_functions) == size:
                        yield cur_order_list
                        cur_order_list = []
                        cur_unique_api_functions = []

                if cur_order_list:
                    yield cur_order_list

            for order_list in _get_sub_order_list_of_size(split_size):
                split_result.append(order_list)
            if len(split_result) > split_number:
                # merge the last two order sets if the last one is too small
                split_result[-2] += split_result[-1]
                split_result.pop()

            return [cls(order_list) for order_list in split_result]

    @classmethod
    def set_size_config(cls, function_set_size: int):
        """
        Set minimum and maximum size of the unique API functions in the set
        based on the configured function set size.

        :param function_set_size: The configured function set size in config["generator"]["function_set_size"]
        """
        # we want a grace for the MAX_SIZE, it can be larger than the function_set_size
        # if the order set is larger than MAX_SIZE, we will split it into multiple order sets
        # each with a size between MIN_SIZE and MAX_SIZE

        # for the above reason, we set MAX_SIZE to be function_set_size * 1.5, MIN_SIZE to be function_set_size * 0.5
        # and ensure that MIN_SIZE <= MAX_SIZE / 2
        cls.MAX_SIZE = function_set_size + function_set_size // 2
        cls.MIN_SIZE = function_set_size // 2
        if cls.MIN_SIZE > cls.MAX_SIZE // 2:
            cls.MIN_SIZE = cls.MAX_SIZE // 2


class OrderSetCollection:
    """
    Class to present a collection of OrderSet.
    """

    def __init__(self, order_sets: list[OrderSet]):
        """
        Initialize the OrderSetCollection

        :param order_sets: The list of OrderSet objects
        """
        self.order_sets = order_sets

    def __len__(self):
        return len(self.order_sets)

    def __getitem__(self, index):
        return self.order_sets[index]

    @classmethod
    def from_raw_order(cls, raw_order: RawCallingOrder) -> "OrderSetCollection":
        """
        Generate an OrderSetCollection from the RawCallingOrder

        :param raw_order: The RawCallingOrder object
        """
        order_sets = []
        for order_list in raw_order.iter_order_list:
            order_sets += OrderSet.from_order_list(order_list)
        return cls(order_sets)

    def dump(self, path: Path):
        """
        Dump the OrderSetCollection to a file

        :param path: The path to the file
        """
        with open(path, "wb") as f:
            pickle.dump(self.order_sets, f)

    @classmethod
    def load(cls, path: Path) -> "OrderSetCollection":
        """
        Load the OrderSetCollection from a file

        :param path: The path to the file
        """
        with open(path, "rb") as f:
            order_sets = pickle.load(f)
        return cls(order_sets)

    def dump_json(self, path: Path):
        """
        Dump the OrderSetCollection to a JSON file, only for human-readable

        :param path: The path to the file
        """
        with open(path, "w") as f:
            json.dump(
                {
                    f"OrderSet {i}": {
                        "size": order_set.size,
                        "apis": [str(api) for api in order_set.order_list],
                    }
                    for i, order_set in enumerate(self.order_sets, 1)
                },
                f,
                indent=4,
                ensure_ascii=False,
            )

    def minimize(self):
        """
        Minimize the OrderSetCollection using Set Cover algorithm
        """
        # Algorithm:
        # 1. Sort the order sets by size in descending order
        # 2. Initialize selected_order_sets = [], covered_api_functions = {api: False}
        # 3. While there are uncovered API functions:
        #    a. For each order set, calculate the number of new covered API functions if it is selected
        #    b. Select the order set that covers the most new API functions
        #    c. Add the selected order set to selected_order_sets and remove it from the order sets
        #    d. Mark the covered API functions as True
        # 4. Return selected_order_sets

        # sort the order sets by size in descending order
        order_sets = sorted(
            self.order_sets, key=lambda order_set: order_set.size, reverse=True
        )

        # initialize selected_order_sets and covered_api_functions
        selected_order_sets = []
        all_api_functions = set()
        for order_set in order_sets:
            all_api_functions.update(order_set.unique_api_functions)
        covered_api_functions = {api: False for api in all_api_functions}

        # while there are uncovered API functions
        while not all(covered_api_functions.values()):
            # for each order set, calculate the number of new covered API functions if it is selected
            new_covered_api_functions: list[list[APIFunction]] = []
            for order_set in order_sets:
                new_covered = []
                for api in order_set.unique_api_functions:
                    if not covered_api_functions[api]:
                        new_covered.append(api)
                new_covered_api_functions.append(new_covered)

            # select the order set that covers the most new API functions
            max_new_covered = 0
            max_new_covered_index = -1
            for i, new_covered in enumerate(new_covered_api_functions):
                if len(new_covered) > max_new_covered:
                    max_new_covered = len(new_covered)
                    max_new_covered_index = i

            # add the selected order set to selected_order_sets and remove it from the order sets
            selected_order_sets.append(order_sets[max_new_covered_index])
            for api in new_covered_api_functions[max_new_covered_index]:
                covered_api_functions[api] = True
            order_sets.pop(max_new_covered_index)

        # set the selected order sets
        self.order_sets = selected_order_sets


class ConsumerCallGraphBuilder:
    """
    Class for building Call Graph from consumer
    """

    # The path to the CGprocessor binary
    PROCESSOR_BIN: Path = None
    # The pool size
    POOL_SIZE: int = cpu_count()
    # The extra build arguments for the consumer code
    BUILD_ARGS = []

    def __init__(
        self,
        api_collection: APICollection,
        header_files: list[Path],
        consumer_sources: list[Path],
    ):
        """
        Initialize the Call Graph Builder

        :param api_collection: The APICollection object
        :param header_files: The list of header files from the APIExtractor
        :param consumer_sources: The list of consumer source files
        """
        self.api_collection = api_collection
        self.header_files = header_files
        self.consumer_sources = consumer_sources

    @classmethod
    def from_library_config(
        cls,
        library_config: dict,
        api_collection: APICollection,
        header_files: list[Path],
    ) -> "ConsumerCallGraphBuilder":
        """
        Initialize the Call Graph Builder from the library configuration

        :param library_config: The library configuration
        :param api_collection: The APICollection object
        :param header_files: The list of header files from the APIExtractor
        """
        consumer_paths = [Path(_) for _ in library_config["consumer_case_paths"]]
        exclude_paths = [Path(_) for _ in library_config["exclude_paths"]]
        SOURCE_SUFFIX = [".c", ".cpp", ".cc", ".cxx", ".c++"]
        consumer_files: list[Path] = []

        for consumer_path in consumer_paths:
            if consumer_path.is_file():
                consumer_files.append(consumer_path)
            elif consumer_path.is_dir():
                for suffix in SOURCE_SUFFIX:
                    consumer_files += list(consumer_path.rglob(f"*{suffix}"))
            else:
                logger.warning(f"Invalid consumer path {consumer_path}")

        # filter out the exclude paths
        consumer_files = [
            file.resolve()
            for file in consumer_files
            if not path_in_paths(file, exclude_paths)
        ]

        logger.debug(
            f"Found {len(consumer_files)} consumer files in consumer paths:\n{'\n'.join([str(file) for file in consumer_files])}"
        )

        return cls(api_collection, header_files, consumer_files)

    def build_graph(self) -> CallGraph:
        """
        Build the Call Graph from the consumer

        :return: The Call Graph
        """
        call_graph = CallGraph(self.api_collection)

        for (
            _,
            caller_name,
            caller_location,
            callee_name,
            callee_location,
        ) in self.calling_pairs:
            call_graph.add_call(
                caller_name, caller_location, callee_name, callee_location
            )

        return call_graph

    def compose_order_sets(self):
        """
        Compose the API order sets, each set contains a list of API functions that are called in order,
        and minimize the order sets
        """

        def extract_raw_order() -> RawCallingOrder:
            calling_order = RawCallingOrder()

            for (
                calling_pos,
                caller_name,
                caller_location,
                _,
                callee_location,
            ) in self.calling_pairs:
                api = CallGraph.api_collection.get_by_decl_location(callee_location)
                if api is None:
                    api = CallGraph.api_collection.get_by_location(callee_location)
                if api is None:
                    continue

                # we get an API callee, add it to the calling order
                calling_order.add_api_call(
                    calling_pos, caller_name, caller_location, api
                )

            return calling_order

        raw_order = extract_raw_order()
        order_set_collection = OrderSetCollection.from_raw_order(raw_order)
        order_set_collection.minimize()

        return order_set_collection

    @cached_property
    def _include_arg(self) -> str:
        """
        The include arguments for the CGprocessor binary
        """
        header_paths = set(file.parent for file in self.header_files)
        return " ".join(f"-I {header_path}" for header_path in header_paths)

    @cached_property
    def calling_pairs(self) -> list[tuple[FilePos, str, str, str, str]]:
        """
        Process the consumer files and get the caller-callee pairs

        :return: The list of position-caller-callee pairs, like (position, caller_name, caller_location, callee_name, callee_location)
        """
        pairs = []

        progress_bar = tqdm(
            total=len(self.consumer_sources),
            desc="Running AST CallGraph Processor for consumer code",
            unit="file",
            leave=False,
            colour="YELLOW",
        )

        def _process_one_consumer_with_progress(consumer_file: Path):
            result = self._process_one_consumer(consumer_file)
            progress_bar.update(1)
            return result

        if self.POOL_SIZE == 1:
            for consumer_file in self.consumer_sources:
                pairs += _process_one_consumer_with_progress(consumer_file)
        else:
            with ThreadPoolExecutor(max_workers=self.POOL_SIZE) as executor:
                pairs = sum(
                    executor.map(
                        _process_one_consumer_with_progress, self.consumer_sources
                    ),
                    [],
                )

        return pairs

    def _process_one_consumer(
        self, consumer_file: Path
    ) -> list[tuple[FilePos, str, str, str, str]]:
        """
        Process one consumer file and get the caller-callee pairs

        :param consumer_file: The consumer file
        :return: The list of position-caller-callee pairs, like (position, caller_name, caller_location, callee_name, callee_location)
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
            cmd = f"{self.PROCESSOR_BIN} {consumer_file} -o {cg_file} -- {self._include_arg}"
            if self.BUILD_ARGS:
                cmd += f" {' '.join(self.BUILD_ARGS)}"
            logger.debug(f"Running CGprocessor for consumer {consumer_file}: \n{cmd}")
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
                    f"CGprocessor warning/error for consumer {consumer_file}:\n{output}"
                )
            if result.returncode != 0:
                logger.error(
                    f"Failed to run CGprocessor for consumer {consumer_file}: \n{cmd}\nerror: \n{result.stderr}"
                )
                return []

            # load the cg.json file
            try:
                with open(cg_file, "r") as f:
                    cg = json.load(f)
            except Exception as e:
                logger.error(f"Failed to load cg.json from {cg_file}: {e}")
                return []

            # get the caller-callee pairs
            # they are like:
            # {
            #   "/promefuzz/database/rapidcsv/latest/out/fuzz_driver/fuzz_driver_183.cpp:52:13": {
            #     "calleeDeclLoc": "/promefuzz/database/rapidcsv/latest/code/src/rapidcsv.h:526:10",
            #     "calleeName": "rapidcsv::Document::Load",
            #     "callerDeclLoc": "/promefuzz/database/rapidcsv/latest/out/fuzz_driver/fuzz_driver_183.cpp:22:16",
            #     "callerName": "LLVMFuzzerTestOneInput"
            #   },
            #   ...
            # }
            pairs = []
            for calling_loc, calling_info in cg.items():
                try:
                    calling_pos = FilePos.from_location_line(calling_loc)
                except Exception as e:
                    logger.error(
                        f"Error processing calling location {calling_loc}: {e}"
                    )
                    continue
                pairs.append(
                    (
                        calling_pos,
                        calling_info["callerName"],
                        calling_info["callerDeclLoc"],
                        calling_info["calleeName"],
                        calling_info["calleeDeclLoc"],
                    )
                )
            if not pairs:
                logger.warning(
                    f"No caller-callee pairs found for consumer {consumer_file}."
                )
            else:
                logger.debug(
                    f"Found {len(pairs)} caller-callee pairs for consumer {consumer_file}."
                )
            return pairs
