import sys
import tomllib
from pathlib import Path
from loguru import logger
from multiprocessing import Pool

from asan import ASan

if __name__ == "__main__":
    # p = Pool(20)
    # p.map_async(run_asan, id_list)
    try:
        path_config = Path(sys.argv[1])
    except:
        logger.error("python run_asan.py fuzz.toml")
        exit(-1)
    config = tomllib.loads(path_config.read_text())

    asan_path = Path("./asan")
    if not asan_path.exists():
        asan_path.mkdir()

    project_name = "ngiflib"
    version = "latest"
    fuzz_id = "promefuzz"

    list_out_id = ["promefuzz_24_0", "promefuzz_24_1", "promefuzz_24_2", "promefuzz_24_3"]

    asan = ASan(config)
    for out_id in list_out_id:
        asan.run(project_name, version, fuzz_id, out_id, 24)
