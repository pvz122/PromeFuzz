from loguru import logger
from pathlib import Path
from sys import exit
from shutil import which
import tomlkit, tomllib
from typing import Dict, Any
import sys
import os

libraries = {
    "c-ares": "7978cf7",
    "curl": "4c50998",
    "lcms": "04ace9c",
    "libjpeg-turbo": "36ac5b84",
    "sqlite3": "557974e",
    "libaom": "99fcd81",
    "libpcap": "2559282",
    "libvpx": "9514ab6",
    "zlib": "5a82f71",
    "re2": "c84a140",
    "libmagic": "dadc01f",
    "libpng": "738f5e7",
    "ngiflib": "db19270",
    "ffjpeg": "caade6",
    "liblouis": "3d95765",
    "libtiff": "fcd4c86",
    "cjson": "12c4bf1",
    "pugixml": "06318b0",
    "tinygltf": "a5e653e",
    "exiv2": "04e1ea3",
    "loguru": "4adaa18",
    "rapidcsv": "083851d",
}
list_libraries = [lib for lib in libraries.keys()]

aflpp_args = {
    "zlib": "-t 1000",
    "sqlite3": "-x /promefuzz/database/sqlite3/sql.dict"
}

def get_aflpp() -> Path:
    """
    Get AFL++ path.

    :return: AFL++ path
    """
    # Test if AFLPP_PATH is set
    if (path_aflpp := os.getenv("AFLPP_PATH")) is None:
        path_aflpp = which("afl-fuzz")
        if path_aflpp is None:
            logger.critical(
                "Please install AFL++ and set the AFLPP_PATH environment variable"
            )
            exit(1)
        else:
            path_aflpp = Path(path_aflpp).parent

    # Convert to Path and test if AFLPP_PATH is a directory
    try:
        path_aflpp_resolved = Path(path_aflpp).resolve(strict=True)
    except (FileNotFoundError, OSError) as e:
        logger.critical(
            f"AFL++ path '{path_aflpp}' does not exist or is not accessible: {e}"
        )
        exit(1)

    # Test if afl-clang-fast exists
    path_compiler = path_aflpp_resolved / "afl-clang-fast"
    if not path_compiler.exists():
        logger.critical(f"Required AFL++ compiler '{path_compiler}' does not exist")
        exit(1)

    # Additional check for afl-clang-fast++
    path_compiler_cpp = path_aflpp_resolved / "afl-clang-fast++"
    if not path_compiler_cpp.exists():
        logger.warning(f"AFL++ C++ compiler '{path_compiler_cpp}' does not exist")

    return path_aflpp_resolved


def load_config_file(config_path: Path) -> Dict[str, Any]:
    """Load and parse a TOML configuration file.

    :param config_path: Path to the configuration file
    :return: Dict[str, Any]: Configuration data
    :raises SystemExit: If configuration file cannot be loaded
    """
    try:
        with open(config_path, "rb") as f:
            return tomllib.load(f)
    except FileNotFoundError:
        logger.error(f"Configuration file not found: {config_path}")
        logger.info("Run './PromeFuzz.py configure init' to create a configuration file")
        sys.exit(1)
    except tomllib.TOMLDecodeError as e:
        logger.error(f"Invalid TOML syntax in {config_path}: {e}")
        sys.exit(1)


def save_config_file(config_path: Path, config_data: Dict[str, Any]) -> bool:
    """Save configuration data to a TOML file without comments."""
    try:
        # Create clean TOML document
        doc = tomlkit.document()

        # Convert dict to tomlkit document
        def dict_to_tomlkit(data, doc_section=None):
            if doc_section is None:
                doc_section = doc

            for key, value in data.items():
                if isinstance(value, dict):
                    table = tomlkit.table()
                    dict_to_tomlkit(value, table)
                    doc_section[key] = table
                else:
                    doc_section[key] = value

        dict_to_tomlkit(config_data)

        with open(config_path, "w", encoding="utf-8") as f:
            tomlkit.dump(doc, f)
        return True

    except Exception as e:
        logger.error(f"Failed to save configuration file {config_path}: {e}")
        return False
