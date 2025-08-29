"""
Calculate the type&scope relevance of API functions
"""

from abc import ABC, abstractmethod
from pathlib import Path
import csv
import pickle
from loguru import logger

from .api import APICollection
from .meta import Meta
from .consumer import CallGraph, CallGraphNode
from .information import InfoRepository, FunctionInfo


class Relevance(ABC):
    """
    The class to store the relevance of the API functions
    """

    def __init__(self, api_collection: APICollection):
        """
        Initialize the relevance

        :param api_collection: The API functions
        """
        self.api_collection = api_collection

        # Set the relevance of all the combinations to 0
        self.relev: dict[tuple[str, str], float] = {}
        func_locs = [func.loc for func in api_collection.safe_iter]
        for func_comb in self._iter_combinations(func_locs):
            self.set_relevance(*func_comb, 0)

        # Calculate the relevance
        self._calc_relevance()

    @abstractmethod
    def _calc_relevance(self):
        """
        Calculate the relevance of the API functions, should be implemented in subclasses
        """
        ...

    @staticmethod
    def _iter_combinations(func_locs: list[str]):
        """
        Iterate all the combinations of functions in the list

        :param func_locs: The list of function locations
        :return: The tuple of function locations
        """
        for i, func_loc_a in enumerate(func_locs):
            for func_loc_b in func_locs[i + 1 :]:
                yield func_loc_a, func_loc_b

    @staticmethod
    def _get_key(func_loc_a: str, func_loc_b: str) -> tuple[str, str]:
        """
        Get the key for the relevance dict

        :param func_loc_a: The location of function A
        :param func_loc_b: The location of function B
        :return: The key for the relevance dict
        """
        return tuple(sorted([func_loc_a, func_loc_b]))

    def get_relevance(self, func_loc_a: str, func_loc_b: str) -> float:
        """
        Get the relevance of the two functions

        :param func_loc_a: The location of function A
        :param func_loc_b: The location of function B
        :return: The relevance of the two functions
        """
        return self.relev[self._get_key(func_loc_a, func_loc_b)]

    def set_relevance(self, func_loc_a: str, func_loc_b: str, relevance: float):
        """
        Set the relevance of the two functions

        :param func_loc_a: The location of function A
        :param func_loc_b: The location of function B
        :param relevance: The relevance of the two functions
        """
        self.relev[self._get_key(func_loc_a, func_loc_b)] = relevance

    def dump(self, path: Path):
        """
        Dump the relevance to a file using pickle

        :param path: The save path
        """
        with open(path, "wb") as f:
            pickle.dump(self.relev, f)

    @classmethod
    def load(cls, path: Path):
        """
        Load the relevance from a file using pickle

        :param path: The load path
        :return: The relevance
        """
        if not path.is_file():
            raise ValueError(f"The relevance file is not found at {path}.")
        with open(path, "rb") as f:
            relev = pickle.load(f)
        loaded = cls.__new__(cls)
        loaded.relev = relev
        return loaded

    def dump_csv(self, path: Path):
        """
        Dump the relevance to a CSV file, only for visualization, not for loading back

        :param path: The save path
        """
        with open(path, "w", newline="") as f:
            writer = csv.writer(f)
            writer.writerow(["func_a", "func_b", "relevance"])
            for (func_loc_a, func_loc_b), relevance in self.relev.items():
                writer.writerow(
                    [
                        f"{self.api_collection.get_by_location(func_loc_a).name}@({func_loc_a.split('/')[-1]})",
                        f"{self.api_collection.get_by_location(func_loc_b).name}@({func_loc_b.split('/')[-1]})",
                        relevance,
                    ]
                )


class TypeRelevance(Relevance):
    """
    Class to store the type relevance of the API functions (API with same return type and parameters)
    """

    def __init__(self, api_collection: APICollection, meta: Meta):
        """
        Initialize the type relevance

        :param api_collection: The API functions
        :param meta: The meta information
        """
        self.meta = meta
        super().__init__(api_collection)

    def _calc_relevance(self):
        """
        Calculate the type relevance of the API functions
        """

        def get_types(func_loc: str) -> list[str]:
            """
            Get the types of the function

            :param func_loc: The location of the function
            """
            try:
                func = self.meta.functions_ori[func_loc]
            except KeyError:
                logger.error(
                    f"Function not found in meta when calculating relevance: {func_loc}"
                )
                return []
            types = [func["return"]["baseType"]]
            types.extend([param["baseType"] for param in func["param"]])
            # remove all void types
            return [t for t in types if t != "void"]

        def root_mean_square(values: list[float]) -> float:
            """
            Calculate the root mean square of the values

            :param values: The list of values
            """
            return (sum([v**2 for v in values]) / len(values)) ** 0.5

        def calc_commonality(types_a: list[str], types_b: list[str]) -> float:
            """
            Calculate the commonality of the types

            :param types_a: The types of function A
            :param types_b: The types of function B
            """
            types_a_len = len(types_a)
            types_b_len = len(types_b)
            if types_a_len == 0 or types_b_len == 0:
                return 0

            common_types_a = len([t for t in types_a if t in types_b])
            common_types_b = len([t for t in types_b if t in types_a])
            return root_mean_square(
                [common_types_a / types_a_len, common_types_b / types_b_len]
            )

        for func_comb in self.relev.keys():
            types_a = get_types(func_comb[0])
            types_b = get_types(func_comb[1])
            self.set_relevance(*func_comb, float(calc_commonality(types_a, types_b)))


class ClassScopeRelevance(Relevance):
    """
    Class to store the class scope relevance of the API functions (API in same class)
    """

    def __init__(self, api_collection: APICollection, info_repo: InfoRepository):
        """
        Initialize the class scope relevance

        :param api_collection: The API functions
        :param info_repo: The information repository
        """
        self.info_repo = info_repo
        super().__init__(api_collection)

    def _calc_relevance(self):
        """
        Calculate the class scope relevance of the API functions
        """

        def is_in_same_class(func_a: FunctionInfo, func_b: FunctionInfo) -> bool:
            """
            Whether the two functions are in the same class
            """
            return func_a.heldby_class == func_b.heldby_class

        for func_comb in self.relev.keys():
            func_a = self.info_repo.get_info(func_comb[0], FunctionInfo)
            func_b = self.info_repo.get_info(func_comb[1], FunctionInfo)
            if func_a is None or func_b is None:
                logger.error(
                    f"Function not found in info when calculating relevance: {func_comb}"
                )
                continue

            self.set_relevance(*func_comb, 1 if is_in_same_class(func_a, func_b) else 0)


class CallScopeRelevance(Relevance):
    """
    Class to store the call scope relevance of the API functions (API called by same function)
    """

    def __init__(self, api_collection: APICollection, call_graph: CallGraph):
        """
        Initialize the call scope relevance

        :param api_collection: The API functions
        :param call_graph: The call graph
        """
        self.call_graph = call_graph
        super().__init__(api_collection)

    def _calc_relevance(self):
        """
        Calculate the call scope relevance of the API functions
        """
        # The intuition is that the closer the API functions are in the call graph,
        # the more likely they are related. For example, if the call graph is like:
        # main -> foo -> API1
        #             -> API2
        #      -> bar -> API3
        # then API1 and API2 should have higher relevance than API1 and API3.
        # Say the distance between two functions is the number of edges between them,
        # then the relevance of two functions can be calculated as:
        # 1 / (distance - 1)    if distance > 1 (If two functions are directly called by the same function, the relevance is 1)
        # 0                     if distance = 1 (This should not happen, all API functions should be the leaf nodes in the consumer call graph)
        # 0                     if distance = ∞

        # ALGORITHM:
        # For each API function node in the CallGraph, use BFS to traverse the graph:
        #    1. If the node is not an API function, skip
        #    2. If the node is an API function, calculate the relevance as 1 / (distance - 1),
        #        and set the relevance to the maximum of the current relevance and the calculated relevance

        def relev(distance: int) -> float:
            """
            The piecewise function to calculate the relevance
            """
            return (1 / (distance - 1)) if distance > 1 else 0

        for api_node in self.call_graph.api_nodes:
            for node, distance in self.call_graph.traverse(
                api_node, is_directed_graph=False
            ):
                if node.api is not None and node != api_node:
                    new_relev = relev(distance)
                    key = self._get_key(api_node.api.loc, node.api.loc)
                    self.set_relevance(*key, max(self.get_relevance(*key), new_relev))


class RelevanceCalculator:
    """
    Class to calculate the relevance of two functions from all relevant aspects
    """

    def __init__(self):
        """
        Initialize the relevance calculator
        """
        self.relevances: list[tuple[Relevance, float]] = []

    def add_relevance_aspect(self, relevance: Relevance, weight: float):
        """
        Add a relevance aspect to the calculator

        :param relevance: The relevance to add
        :param weight: The weight of the relevance
        """
        self.relevances.append((relevance, weight))

    def get_relevance(self, func_loc_a: str, func_loc_b: str) -> float:
        """
        Get the relevance of the two functions

        :param func_loc_a: The location of function A
        :param func_loc_b: The location of function B
        :return: The relevance of the two functions
        """
        if not self.relevances:
            # avoid division by zero
            return 0

        relev_sum = 0
        weight_sum = 0
        for relevance, weight in self.relevances:
            relev_sum += relevance.get_relevance(func_loc_a, func_loc_b) * weight
            weight_sum += weight
        return relev_sum / weight_sum
