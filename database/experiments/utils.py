from loguru import logger
from pathlib import Path
from sys import exit
from shutil import which
import os

libraries = {
    "c-ares": "7978cf7",
    "curl": "4c50998",
    "lcms": "04ace9c",
    "libjpeg-turbo": "36ac5b84",
    "sqlite3": "7903db4",
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
    "rapidcsv": "083851d"
}
list_libraries = [lib for lib in libraries.keys()]


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
