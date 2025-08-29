"""
Extract API functions from the library.
"""

from pathlib import Path
from loguru import logger
from multiprocessing import cpu_count
from dataclasses import dataclass
import json
import pickle

from src.utils import path_in_paths, parse_location, remove_template_parts_in_name
from src import vars as global_vars
from .meta import Meta


@dataclass
class APIFunction:
    """
    Class to represent an API function.
    """

    header: str
    """
    The header file where the API function is located.
    """

    name: str
    """
    The name of the API function.
    """

    loc: str
    """
    The location of the API function, as an identifier.
    """

    decl_loc: str
    """
    The declaration location (in the header) of the API function.
    """

    def __eq__(self, other):
        if not isinstance(other, APIFunction):
            return False
        return self.loc == other.loc

    def __hash__(self):
        return hash(self.loc)

    def __str__(self):
        return f"{self.name} at {self.loc.split('/')[-1]} in {Path(self.header).name}"

    def __repr__(self):
        return self.__str__()


class APICollection:
    """
    Class to store the API functions.
    """

    def __init__(self, api_functions: list[APIFunction]):
        """
        Initialize the API functions.

        :param api_functions: The API functions list
        """
        self.funcs = api_functions

    @property
    def count(self):
        """
        Get the count of the API functions.
        """
        return len(self.funcs)

    @property
    def header_paths(self):
        """
        Get all header paths in the API functions

        :return: A list of header paths
        """
        return list(set(func.header for func in self.funcs))

    @property
    def function_names(self):
        """
        Get all function names in the API functions

        :return: A list of function names
        """
        return list(set(func.name for func in self.funcs))

    @property
    def function_locations(self):
        """
        Get all function locations in the API functions

        :return: A list of function locations
        """
        return list(func.loc for func in self.funcs)

    @property
    def function_decl_locations(self):
        """
        Get all function declaration locations in the API functions

        :return: A list of function declaration locations
        """
        return list(func.decl_loc for func in self.funcs)

    def dump(self, path: Path):
        """
        Dump the API functions to a file.

        :param path: The save path
        """
        with open(path, "wb") as f:
            pickle.dump(self.funcs, f)

    def dump_to_json(self, path: Path):
        """
        Dump the API functions to a JSON file. Only for readability, not for loading back.

        :param path: The save path
        """
        api_functions = dict()
        for api_func in self.funcs:
            api_functions.setdefault(api_func.header, dict()).setdefault(
                api_func.name, []
            ).append(
                {
                    "loc": api_func.loc,
                    "decl_loc": api_func.decl_loc,
                }
            )
        with open(path, "w") as f:
            json.dump(api_functions, f, indent=4)

    @classmethod
    def load(cls, path: Path):
        """
        Load the API functions from a file.

        :param path: The load path
        :return: The API functions
        """
        if not path.is_file():
            raise ValueError(f"The API functions file is not found at {path}.")
        with open(path, "rb") as f:
            api_functions = pickle.load(f)
        return cls(api_functions)

    @property
    def safe_iter(self):
        """
        Iterate the API functions. During the iteration, the API functions can be safely modified.

        :return: The API function generator
        """
        snapshot = self.funcs.copy()
        for api_func in snapshot:
            yield api_func

    def get_by_location(self, loc: str) -> APIFunction | None:
        """
        Get the API function by location.

        :param loc: The location
        :return: The API function, or None if not found
        """
        # cache lookup table
        if not hasattr(self, "loc_lookup_dict"):
            self.loc_lookup_dict = dict()
            for func in self.funcs:
                self.loc_lookup_dict[func.loc] = func
        return self.loc_lookup_dict.get(loc, None)

    def get_by_decl_location(self, loc: str) -> APIFunction | None:
        """
        Get the API function by declaration location.

        :param loc: The location
        :return: The API function, or None if not found
        """
        # cache lookup table
        if not hasattr(self, "decl_loc_lookup_dict"):
            self.decl_loc_lookup_dict = dict()
            for func in self.funcs:
                self.decl_loc_lookup_dict[func.decl_loc] = func
        return self.decl_loc_lookup_dict.get(loc, None)

    def get_by_name(self, func_name: str) -> list[APIFunction]:
        """
        Get the API functions by name.

        :param func_name: The function name
        :return: The list of API functions
        """
        # cache lookup table
        if not hasattr(self, "name_lookup_dict"):
            self.name_lookup_dict = dict()
            for func in self.funcs:
                self.name_lookup_dict.setdefault(func.name, []).append(func)
        return self.name_lookup_dict.get(func_name, [])

    def get_locations_by_name(self, func_name: str):
        """
        Get the locations of the API functions with the same name.

        :param func_name: The function name
        :return: The list of locations
        """
        return [func.loc for func in self.get_by_name(func_name)]

    def remove(self, api_function: APIFunction):
        """
        Remove an API function.

        :param api_function: The API function to remove
        """
        self.funcs.remove(api_function)
        if hasattr(self, "loc_lookup_dict"):
            self.loc_lookup_dict.pop(api_function.loc, None)
        if hasattr(self, "decl_loc_lookup_dict"):
            self.decl_loc_lookup_dict.pop(api_function.decl_loc, None)
        if hasattr(self, "name_lookup_dict"):
            self.name_lookup_dict.pop(api_function.name, None)

    def append(self, api_function: APIFunction):
        """
        Append an API function.

        :param api_function: The API function to append
        """
        self.funcs.append(api_function)
        if hasattr(self, "loc_lookup_dict"):
            self.loc_lookup_dict[api_function.loc] = api_function
        if hasattr(self, "decl_loc_lookup_dict"):
            self.decl_loc_lookup_dict[api_function.decl_loc] = api_function
        if hasattr(self, "name_lookup_dict"):
            self.name_lookup_dict.setdefault(api_function.name, []).append(api_function)

    def has(self, api_function: APIFunction):
        """
        Check if the API function exists.

        :param api_function: The API function to check
        :return: True if exists, False otherwise
        """
        return api_function in self.funcs

    def __len__(self):
        return len(self.funcs)

    def __str__(self):
        return "\n".join(
            f"{func.name} at {func.loc.split("/")[-1]} in {Path(func.header).name}"
            for func in self.funcs
        )


class APIExtractor:
    """
    API extractor class
    """

    RUN_DUMMY_TEST = False

    def __init__(
        self,
        meta: Meta,
        header_paths: list[Path],
        exclude_paths: list[Path] = [],
        ban_list: list[str] = [],
    ):
        """
        Initialize the API extractor

        :param meta: Meta object
        :param header_paths: List of header paths
        :param exclude_paths: List of paths to exclude
        :param ban_list: List of function locations to ban
        """
        self.meta = meta
        self._get_header_files(header_paths, exclude_paths)
        self.ban_list = ban_list

    @classmethod
    def from_library_config(cls, library_config: dict, meta: Meta):
        """
        Initialize the API extractor from the library configuration.

        :param library_config: The library configuration.
        :param meta: The meta object.
        """
        header_paths = [Path(_) for _ in library_config["header_paths"]]
        exclude_paths = [Path(_) for _ in library_config["exclude_paths"]]
        ban_list_path = library_config["api_ban_list_path"]
        if ban_list_path:
            with open(ban_list_path, "r") as f:
                ban_list = json.load(f)
        else:
            ban_list = []
        return cls(meta, header_paths, exclude_paths, ban_list)

    def _get_header_files(
        self, header_paths: list[Path], exclude_paths: list[Path] = []
    ):
        """
        Get the header files from the header paths

        :param header_paths: List of header paths
        :param exclude_paths: List of paths to exclude
        """
        HEADER_SUFFIXES = [".h", ".hpp", ".hxx", ".hh"]
        header_files: list[Path] = []

        for header_path in header_paths:
            if header_path.is_file():
                header_files.append(header_path)
            elif header_path.is_dir():
                for suffix in HEADER_SUFFIXES:
                    header_files.extend(header_path.rglob(f"*{suffix}"))
            else:
                logger.warning(f"Invalid header path {header_path}")

        # filter out the excluded paths
        header_files = [
            file for file in header_files if not path_in_paths(file, exclude_paths)
        ]

        logger.debug(
            f"Found {len(header_files)} header files: {[str(file) for file in header_files]}"
        )
        header_files = [file.resolve() for file in header_files]
        self.header_files = header_files

    def _extract_functions(self) -> APICollection:
        """
        Extract the functions in the header files.

        :return: The extracted functions
        """
        api_functions = list()
        for func_loc, func_obj in self.meta.functions_ori.items():
            # definition file and declaration file
            # usually, a normal function is declared in a header file and defined in a source file
            # a template function is declared and defined in a header file
            # thus, we should both check the definition file and declaration file
            def_file = Path(parse_location(func_loc)[0]).resolve()
            decl_file = (
                Path(parse_location(func_obj["declLoc"])[0]).resolve()
                if func_obj["declLoc"]
                else None
            )

            # check if any of the function locations is in the header files
            for header_file in self.header_files:
                if def_file == header_file or decl_file == header_file:
                    api_func = APIFunction(
                        header=str(header_file),
                        name=func_obj["name"],
                        loc=func_loc,
                        decl_loc=str(
                            func_loc if def_file == header_file else func_obj["declLoc"]
                        ),
                    )
                    api_functions.append(api_func)
                    break
        logger.debug(f"Extracted {len(api_functions)} functions")
        return APICollection(api_functions)

    def _filter_functions(self, api_functions: APICollection):
        """
        Filter the functions extracted.

        :param api_functions: The extracted functions to filter
        """
        filtered_count = 0

        def filter_out(func: APIFunction):
            nonlocal filtered_count
            api_functions.remove(func)
            filtered_count += 1

        for func in api_functions.safe_iter:
            func_obj = self.meta.functions_ori[func.loc]

            # check if the function is an operator (it is strange that some operators do not belong to class)
            if "::operator" in func_obj["name"]:
                filter_out(func)
                continue

            # check if the function is a class method
            heldby_class = func_obj["heldbyClass"]
            if heldby_class:
                if heldby_class not in self.meta.classes:
                    logger.warning(f"Class {heldby_class} not found in the meta data.")
                    filter_out(func)
                    continue

                # check if the function is a class constructor or destructor
                # we use this string comparison filter first
                # for some cases like template functions, the later AST-based filter will work
                if func_obj["name"].split("::")[-1] == heldby_class.split("::")[-1]:
                    filter_out(func)
                    continue
                if "~" in func_obj["name"]:
                    filter_out(func)
                    continue

                # get the class method object where the function is located
                heldby_method = None
                heldby_class_objs = self.meta.classes[heldby_class]
                for heldby_class_obj in heldby_class_objs.values():
                    for _, method_obj in heldby_class_obj["methods"].items():

                        # we use name comparison here, because the function location may be different
                        if (method_obj["name"] == func_obj["name"]) or (
                            # there are cases that the function is a template specialization function
                            # which is not in the original class method list
                            # we remove the template part and compare the name
                            method_obj["name"]
                            == remove_template_parts_in_name(func_obj["name"])
                        ):
                            heldby_method = method_obj
                            break
                    if heldby_method:
                        break
                if not heldby_method:
                    logger.warning(
                        f"Method {func.name} not found in the class {heldby_class}."
                    )
                    filter_out(func)
                    continue

                # check if the function is public, not a operator, virtual function
                if any(
                    [
                        not heldby_method["isPublic"],
                        heldby_method["isOperator"],
                        heldby_method["isVirtual"],
                        heldby_method["isConstructor"],
                        heldby_method["isDestructor"],
                    ]
                ):
                    filter_out(func)
                    continue

        logger.info(f"Filtered out {filtered_count} functions")

    def _ban_functions(self, api_functions: APICollection):
        """
        Ban the functions in the ban list.

        :param api_functions: The API functions to ban
        """
        banned_count = 0
        for ban_loc in self.ban_list:
            api_func = api_functions.get_by_location(str(Path(ban_loc).resolve()))
            if api_func:
                api_functions.remove(api_func)
                banned_count += 1
            else:
                logger.warning(
                    f"API function {ban_loc} in the ban list is not an API function."
                )
        logger.info(f"Banned {banned_count} API functions")

    def extract(self, pool_size: int = cpu_count()) -> APICollection:
        """
        Extract the API from the header files.

        :param pool_size: The pool size for the dummy driver test
        :return: The extracted API dictionary
        """
        # Algorithm:
        # INPUT: meta, header files
        # OUTPUT: api function names in the header files
        # 1. Get all the function in the header files:
        #    For each function in meta.functions, get its locRange and declLocRange
        #    If the loc is in the header files, add the function to the api
        # 2. For each function got in step 1, get its heldbyClass, and locate it as a class method
        #    See if this function isPubic, if not, discard it
        #    See if this function is a constructor, destructor, operator, virtual function, if yes, discard it
        # 3. For each function extracted, test it in a dummy driver
        # 4. Save the extracted API to a file
        #
        # FIXME: Will there be a situation that a header file is separate from the source file and no source file includes it?

        # extract the functions in the header files
        api_functions = self._extract_functions()

        # filter the extracted functions
        self._filter_functions(api_functions)

        # ban functions in the ban list
        if self.ban_list:
            self._ban_functions(api_functions)

        if self.RUN_DUMMY_TEST:
            # to avoid circular import
            from .dummy import DummyTester

            # test the extracted functions in a dummy driver
            logger.info(
                f"Running dummy driver test for the {len(api_functions)} API functions."
            )
            dummy_tester = DummyTester(
                self.meta,
                api_functions,
                saving_dir=Path(global_vars.library_config["output_path"])
                / "preprocessor"
                / "dummy_driver",
            )
            dummy_tester.run(pool_size)

        return api_functions
