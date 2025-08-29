import os
import sys
import tomllib
from pathlib import Path
from loguru import logger
from multiprocessing import Pool

from gcov import GCov

if __name__ == "__main__":
    try:
        path_config = Path(sys.argv[1])
    except:
        logger.error("python run_gcov.py fuzz.toml")
        exit(-1)
    config = tomllib.loads(path_config.read_text())

    gcov_path = Path("./gcov")
    if not gcov_path.exists():
        gcov_path.mkdir()

    project_name = "ngiflib"
    version = "latest"
    fuzz_id = "promefuzz"

    list_out_id = [
        "promefuzz_24_0",
        # "promefuzz_24_1",
        # "promefuzz_24_2",
        # "promefuzz_24_3"
    ]

    gcov = GCov(config)
    for out_id in list_out_id:
        gcov.run(project_name, version, fuzz_id, out_id, 24)
