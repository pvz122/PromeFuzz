from pathlib import Path
import json

from src.generator.extractor import SourceFileReader

this_dir = Path(__file__).parent

def run():
    with open(this_dir / "pugixml.json") as f:
        meta = json.load(f)

    print("Testing SourceFileReader.read_function_signature")

    with open(this_dir / "pugixml_func_defs.cpp", "w") as f:
        for func_loc, func_obj in meta["functions"].items():
            locrange = func_obj["locRange"]
            if func_obj["declLocRange"]:
                locrange = func_obj["declLocRange"]
            is_template = func_obj["isTemplate"]

            function_def = SourceFileReader.read_function_signature(locrange, is_template)[2]

            f.write(f"// ==== {func_loc} at {locrange} ====\n")
            f.write(f"{function_def}\n\n")

    print("Done, check pugixml_func_defs.json")

    print("Testing SourceFileReader.read_complex_composite_definition")

    with open(this_dir / "pugixml_composite_defs.cpp", "w") as f:
        for composite_loc, composite_obj in meta["composites"].items():
            if members:=composite_obj["members"]:
                locrange = composite_obj["locRange"]
                members_locrange = tuple(member["locRange"] for member in members)
                is_template = composite_obj["isTemplate"]

                composite_def = SourceFileReader.read_complex_composite_definition(locrange, members_locrange, is_template)[2]

                f.write(f"// ==== {composite_loc} at {locrange} ====\n")
                f.write(f"{composite_def}\n\n")
        for enum_loc, enum_obj in meta["enums"].items():
            locrange = enum_obj["locRange"]
            members_locrange = tuple(["<enum>"])
            is_template = False

            composite_def = SourceFileReader.read_complex_composite_definition(locrange, members_locrange, is_template)[2]

            f.write(f"// ==== {enum_loc} at {locrange} ====\n")
            f.write(f"{composite_def}\n\n")

    print("Done, check pugixml_composite_defs.json")

    print("Testing SourceFileReader.read_typedef_definition")

    with open(this_dir / "pugixml_typedef_defs.cpp", "w") as f:
        for typedef_loc, typedef_obj in meta["typedefs"].items():
            locrange = typedef_obj["locRange"]

            typedef_def = SourceFileReader.read_typedef_definition(locrange)[2]

            f.write(f"// ==== {typedef_loc} at {locrange} ====\n")
            f.write(f"{typedef_def}\n\n")

    print("Done, check pugixml_typedef_defs.json")
