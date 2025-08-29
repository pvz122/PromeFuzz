"""
Process the AST meta data.
"""

from pathlib import Path
from functools import cached_property
import json


class Meta:
    """
    The library AST meta data.
    """

    # The meta data attributes.
    META_ATTRS = ["classes", "functions", "composites", "enums", "typedefs"]
    # In total, the Meta provides the following attributes:
    # - meta: The meta data organized by names.
    # - classes, functions, composites, enums, typedefs: The sub meta data organized by names.
    # - meta_ori: The original meta data dict organized by locations.
    # - classes_ori, functions_ori, composites_ori, enums_ori, typedefs_ori: The original sub meta data dict organized by locations.
    # - functions_decl: The functions objects organized by the declaration location.

    def __init__(self, meta_dict: dict):
        """
        Initialize the meta data.

        :param meta_dict: The meta data dict.
        """
        self.meta_ori = meta_dict

    @cached_property
    def meta(self) -> dict:
        """
        The meta data organized by names.
        """
        """
        For example, the meta data is like:
        ```
        {
            "classes": {
                "/promefuzz/library/jsonxx/jsonxx.cc:185:7": {
                    "name": "jsonxx::IOStateMasker",
                    "isAbstract": false,
                    ...
                },
                ...
            },
            ...
        }
        ```
        We will reorganize it to:
        ```
        {
            "classes": {
                "jsonxx::IOStateMasker": {
                    "/promefuzz/library/jsonxx/jsonxx.cc:185:7": {
                        "name": "jsonxx::IOStateMasker",
                        "isAbstract": false,
                        ...
                    },
                    ...
                },
                ...
            },
            ...
        }
        ```
        This is for the convenience of searching by names.
        Note that the reorganized dict is just a wrapper of the original dict.
        Any changes to the reorganized dict will also affect the original dict.
        """
        reorganized_meta = {}
        for key, value in self.meta_ori.items():
            reorganized_meta[key] = {}
            for k, v in value.items():
                if "name" in v:
                    reorganized_meta[key].setdefault(v["name"], {})[k] = v
                else:
                    reorganized_meta[key].setdefault("unknown", {})[k] = v
        return reorganized_meta

    @cached_property
    def functions_decl(self) -> dict:
        """
        The functions objects organized by the declaration location.
        """
        func_ori: dict = self.meta_ori.get("functions", {})
        reorganized_func = {}
        for func_loc, func_obj in func_ori.items():
            if func_decl_loc := func_obj["declLoc"]:
                reorganized_func[func_decl_loc] = func_obj
        return reorganized_func

    def __getattr__(self, item: str):
        """
        Get the sub meta data.
        """
        is_ori = item.endswith("_ori")

        if is_ori:
            item = item.removesuffix("_ori")

        if item not in self.META_ATTRS:
            raise AttributeError(
                f"'{self.__class__.__name__}' object has no attribute '{item}'"
            )

        if is_ori:
            return self.meta_ori.get(item, {})
        else:
            return self.meta.get(item, {})

    @classmethod
    def merge(cls, metas: list["Meta"]) -> "Meta":
        """
        Merge the meta data.

        :param metas: The meta data list.
        :return: The merged meta data.
        """
        merged_meta = {}
        for meta in metas:
            for attr in cls.META_ATTRS:
                merged_meta.setdefault(attr, {}).update(getattr(meta, f"{attr}_ori"))
        return cls(merged_meta)

    def dump(self, output_path: Path):
        """
        Dump the meta data to a file.

        :param output_path: The output path.
        """
        with open(output_path, "w") as f:
            json.dump(self.meta_ori, f, indent=4)

    @classmethod
    def load(cls, input_path: Path) -> "Meta":
        """
        Load the meta data from a file.

        :param input_path: The input path.
        :return: The meta data.
        """
        if not input_path.is_file():
            raise ValueError(f"The meta file is not found at {input_path}.")
        with open(input_path, "r") as f:
            meta_json = json.load(f)
        if not meta_json:
            raise ValueError(f"The meta file is empty.")
        return cls(meta_json)

    def _reorganize_with_names(self, meta: dict) -> dict:
        """
        Reorganize the meta data with names.
        For example, the meta data is like:
        ```
        {
            "classes": {
                "/promefuzz/library/jsonxx/jsonxx.cc:185:7": {
                    "name": "jsonxx::IOStateMasker",
                    "isAbstract": false,
                    ...
                },
                ...
            },
            ...
        }
        ```
        We will reorganize it to:
        ```
        {
            "classes": {
                "jsonxx::IOStateMasker": {
                    "/promefuzz/library/jsonxx/jsonxx.cc:185:7": {
                        "name": "jsonxx::IOStateMasker",
                        "isAbstract": false,
                        ...
                    },
                    ...
                },
                ...
            },
            ...
        }
        ```
        This is for the convenience of searching by names.
        Note that the reorganized dict is just a wrapper of the original dict.
        Any changes to the reorganized dict will also affect the original dict.

        :param meta: The meta data dict.
        :return: The reorganized meta data dict.
        """
        reorganized_meta = {}
        for key, value in meta.items():
            reorganized_meta[key] = {}
            for k, v in value.items():
                if "name" in v:
                    reorganized_meta[key].setdefault(v["name"], {})[k] = v
                else:
                    reorganized_meta[key].setdefault("unknown", {})[k] = v
        return reorganized_meta

    def reorganize_base_to_derived(self):
        """
        Reorganize the classes. Search for the the derived classes of each base class.
        """
        # The dict to store the derive information. As base_class_name: [derived_class_location]
        base_derived_dict = {}

        # First traverse to get base_derived_dict
        for class_loc, class_obj in self.classes_ori.items():
            for base_ABC in class_obj["baseABCs"]:
                base_derived_dict.setdefault(base_ABC, []).append(class_loc)

        # Second traverse to update the derived_classes
        for class_obj in self.classes_ori.values():
            if class_obj["name"] in base_derived_dict and class_obj["isAbstract"]:
                class_obj["ABCDerives"] = base_derived_dict[class_obj["name"]]
            else:
                class_obj["ABCDerives"] = []  # make an empty list for compatibility
