import os
import sys
import tqdm
import tomllib
from pathlib import Path
from loguru import logger

from cov import Cov

if __name__ == "__main__":
    try:
        path_config = Path(sys.argv[1])
    except:
        logger.error("python run_cov.py fuzz.toml")
        exit(-1)
    config = tomllib.loads(path_config.read_text())

    # project_name = "ngiflib"
    project_name = "loguru"
    # project_name = "libtiff"
    version = "latest"
    # fuzz_id = "promefuzz"
    fuzz_id = "ckg"
    # fuzz_id = "pfuzz"

    if fuzz_id == "promefuzz":
        pool_size = 1
    else:
        pool_size = 40

    list_out_id = []
    start_id = 0
    for i in range(0, 1):
        list_out_id.append(f"{fuzz_id}_24_{start_id + i}")

    logger.remove()
    logger.add(
        tqdm.tqdm.write,
        level="INFO",
        format="<green>{time:YYYY-MM-DD HH:mm:ss}</green> | <level>{level}</level> | <cyan>{name}</cyan>:<cyan>{function}</cyan>:<cyan>{line}</cyan> | <level>{message}</level>",
        colorize=True,
    )

    cov = Cov(config)
    for out_id in list_out_id:
        cov.run(project_name, version, fuzz_id, out_id, 24, pool_size=1)
