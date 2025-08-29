import tqdm
import subprocess
from pathlib import Path
from loguru import logger

from extraction import Extraction


class ASan:
    def __init__(self, config: dict):
        self.config = config

    def run(self, project_name, version, fuzz_id, out_id, time):
        try:
            config = self.config[project_name][version][fuzz_id]
        except:
            logger.error(f"{project_name}.{version}.{fuzz_id} not in fuzz config")
            return

        prog_arg = config["cmd"]
        afltype = config["fuzzer"]
        out_base_path = Path(config["out_base_path"]).resolve()
        bin_asan = Path(config["bin_asan"]).resolve(strict=True)

        path_base = out_base_path / f"out_{out_id}"

        e = Extraction(project_name, path_base, afltype)
        # e.flag_print = True
        crashes_list = e.extract(time * 3600, "crashes")
        dict_id_time = e.dict_id_time
        list_id = list(dict_id_time.keys())
        list_id.sort()
        count = 0

        workdir = Path(f"{project_name}/{version}/asan/{out_id}")
        if workdir.exists():
            logger.warning(f"{workdir} exists")
            return
        else:
            workdir.mkdir(parents=True)
        path_asan_log = workdir / "asan.log"
        process_bar = tqdm.tqdm(
            total=len(crashes_list),
            desc=f"Running ASan for {out_id}",
            unit="seed",
            leave=False,
            colour="green",
        )

        def _run_asan(crash):
            id = int(crash.split(":")[1].split(",")[0], 10)
            # continue
            _cmd = f"{bin_asan} {prog_arg.replace('@@', str(Path(crash).resolve(strict=True)))}"

            # if project_name == "jasper" or project_name == "libwav":
            cmd = f"ASAN_OPTIONS='symbolize=1:detect_odr_violation=0:allocator_may_return_null=1' {_cmd}"
            # else:
            #     cmd = (
            #         "ASAN_OPTIONS='symbolize=1:detect_odr_violation=0:allocator_may_return_null=1:detect_leaks=0' timeout -s 9 60 %s 2>> %s 1>/dev/null"
            #         % (_cmd, path_asan_log)
            #     )
            # cmd = "ASAN_OPTIONS=detect_odr_violation=0 timeout -s 9 120 %s 2>> %s 1>/dev/null" % (_cmd, path_asan_log) # For libming ONLY
            logger.debug("running: " + cmd)
            try:
                output = subprocess.run(
                    cmd,
                    shell=True,
                    timeout=120,
                    cwd=workdir,
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.PIPE,
                )
                output_str = output.stderr.decode(errors="ignore")
            except subprocess.TimeoutExpired:
                logger.warning(f"run {crash} for more than 120s")
            finally:
                process_bar.update(1)

            for _ in list_id:
                if _ > id:
                    time_str = f"time={dict_id_time[_]}\n"
                    # print(str(dict_id_time[_]))
                    break
            with path_asan_log.open("a") as file:
                file.write(time_str)
                file.write(f"{crash}\n")
                file.write(output_str)

        for crash in crashes_list:
            _run_asan(crash)
