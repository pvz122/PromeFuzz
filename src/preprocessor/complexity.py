"""
Calculate the complexity of API functions

The intuition is that the scale and complexity of the API functions are not the same.
The more complex an API function is, the more it should be tested in the fuzz driver.
To evaluate the complexity, we consider the following factors:
- The lines of code of the function implementation (LoC)
- The number of reachable functions from the function in the library call graph (NoF)
And we define the complexity of an API function as:
Complexity = MinMax(Sqrt(LoC * (NoF + 1)))
"""

from math import sqrt
import pickle
import csv
from pathlib import Path

from .consumer import CallGraph
from .information import InfoRepository, FunctionInfo
from .api import APICollection, APIFunction


class Complexity:
    """
    Class to store the complexity of all API functions
    """

    def __init__(self, api_collection: APICollection):
        """
        Initialize the Complexity

        :param api_collection: The API functions collection
        """
        self.complexities: dict[APIFunction, float] = {
            api: 0 for api in api_collection.safe_iter
        }  # the raw complexities, without Min-Max normalization
        self.min = 0
        self.max = 0

    def __getitem__(self, api: APIFunction) -> float:
        """
        Retrieve the complexity of an API function.
        """
        if not isinstance(api, APIFunction):
            raise TypeError("APIFunction object is required for indexing.")

        return self.get(api)

    def get(self, api: APIFunction) -> float:
        """
        Retrieve the complexity of an API function.
        """
        if self.max == self.min:
            return 1
        return (self.complexities[api] - self.min) / (self.max - self.min)

    def set_raw(self, api: APIFunction, complexity: float):
        """
        Set the raw complexity of an API function
        """
        self.complexities[api] = complexity

        if complexity < self.min:
            self.min = complexity
        if complexity > self.max:
            self.max = complexity

    def dump(self, file: Path):
        """
        Dump the complexities to a file

        :param file: The file to dump the complexities
        """
        with open(file, "wb") as f:
            pickle.dump(self.complexities, f)

    @classmethod
    def load(cls, file: Path) -> "Complexity":
        """
        Load the complexities from a file

        :param file: The file to load the complexities
        :return: The Complexity object
        """
        with open(file, "rb") as f:
            complexities = pickle.load(f)
        complexity = cls.__new__(cls)
        complexity.complexities = complexities
        complexity.min = min(complexities.values())
        complexity.max = max(complexities.values())
        return complexity

    def dump_csv(self, file: Path):
        """
        Dump the complexities to a CSV file, only for human-readable

        :param file: The file to dump the complexities
        """
        with open(file, "w") as f:
            writer = csv.writer(f)
            writer.writerow(["API", "Complexity"])
            for api in self.complexities.keys():
                writer.writerow([str(api), self[api]])

class ComplexityCalculator:
    """
    Class for calculating the complexity of API functions
    """

    def __init__(
        self,
        api_collection: APICollection,
        info_repo: InfoRepository,
        library_call_graph: CallGraph,
    ):
        """
        Initialize the Complexity

        :param api_collection: The API functions collection
        :param info_repo: The information repository
        :param library_call_graph: The library call graph
        """
        self.api_collection = api_collection
        self.info_repo = info_repo
        self.call_graph = library_call_graph

    def calculate(self) -> Complexity:
        """
        Calculate the complexities of the API functions

        :return: The Complexity object
        """

        def _get_LoC(api: APIFunction) -> int:
            impl_start, impl_end = self.info_repo.get_info(
                api.loc, FunctionInfo
            ).impl_range
            if impl_start is None or impl_end is None:
                return 0
            return impl_end.line - impl_start.line + 1

        def _get_NoF(api: APIFunction) -> int:
            if not hasattr(self, "NoF_dict"):
                # Calculate the number of reachable functions for each API function
                self.NoF_dict = {}
                for api_node in self.call_graph.api_nodes:
                    self.NoF_dict[api_node.api] = len(
                        self.call_graph.reachable_nodes(api_node)
                    )
            return self.NoF_dict.get(api, 0)

        complexities = Complexity(self.api_collection)
        for api in self.api_collection.safe_iter:
            complexities.set_raw(api, sqrt(_get_LoC(api) * (_get_NoF(api) + 1)))

        return complexities
