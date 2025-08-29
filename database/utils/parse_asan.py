import os
import sys
import json
import hashlib
from pathlib import Path

id_list = []

dic_target = dict()


def parse_log(path_log):
    dict_bug_time = dict()
    # list_bug_line = []
    # list_time = []

    asan_flag = 0
    bug_flag = 0
    f = open(path_log, "rb")
    line = f.readline()
    time = None
    seed = None
    list_asan_report = []
    while line:
        if asan_flag == 0:
            # print(line)
            if line.find(b"time=") == 0:
                time = line.rstrip().split(b"=")[1]
                line = f.readline()
                seed = line.rstrip()
            try:
                # print(line.split()[0].split("==")[2])
                if line.split(b"==")[2].split()[0] == b"ERROR:":
                    # print("asan_flag = 1 now")
                    list_asan_report = []
                    list_asan_report.append(line.decode())
                    asan_flag = 1
                    bug_flag = 1
                    error_type = line.split(b"==")[2].split()[2]
            except:
                line = f.readline()
                continue
        elif asan_flag == 1:
            list_asan_report.append(line.decode(errors="ignore"))
            if bug_flag:
                try:
                    if line.split()[0] == b"#0":
                        while (
                            line.find(b"lib/asan") > 0
                            or line.find(b"glibc-2.23") > 0
                            or line.find(b"compiler-rt/lib") > 0
                            or line.find(b"/lib/x86_64-linux-gnu") > 0
                            or line.find(b"syscall-template.S") > 0
                            or line.find(b"magma_log") > 0
                            or line.find(b"(BuildId:") > 0
                            or line.find(b"usr/lib/gcc") > 0
                        ):
                            line = f.readline()
                            list_asan_report.append(line.decode())
                        bug_func = line.split()[3]
                        bug_line = (
                            line.split()[-1] + b" " + bug_func + b" " + error_type
                        )
                        # print(type(bug_line), type(dict_bug_time))
                        bug_line = bug_line.decode()
                        if bug_line not in dict_bug_time:
                            dict_bug_time[bug_line] = {
                                "time": time,
                                "report": list_asan_report,
                                "seed": seed.decode(),
                            }
                            # list_bug_line.append(bug_line)
                            # list_time.append(time)

                        # if (line.find("lib/asan") < 0):
                        #     list_bug_line.add(line.split()[-1]+" "+error_type)
                        # else:
                        #     line = f.readline()
                        #     list_bug_line.add(line.split()[-1]+" "+error_type)
                        bug_flag = 0
                        # print("asan_flag = 0")
                except:
                    line = f.readline()
                    list_asan_report.append(line.decode())
                    # print("?")
                    continue
            if line.find(b"==ABORTING") >= 0:
                asan_flag = 0
        else:
            print("error")
            exit()
        line = f.readline()

    # print(list_bug_line)
    # print(dict_bug_time)
    return dict_bug_time


def parse_dir(dirpath, fuzz_id):
    list_logpaths = os.listdir(dirpath)
    # fuzz_id = list_logpaths[0].split("_")[0]
    print(fuzz_id, end=" ")
    dict_asan = dict()
    for logpath in list_logpaths:
        if (
            logpath.find(".log") > 0
            and os.path.isfile(dirpath + "/" + logpath)
            and logpath.find(fuzz_id) == 0
        ):
            idx = int(str(logpath).split("_")[3], 10)
            dict_asan[idx] = parse_log(dirpath + "/" + logpath)
    list_idx = list(dict_asan.keys())
    list_idx.sort()
    set_bug = set()
    for _ in list_idx:
        set_bug = set_bug.union(set(dict_asan[_].keys()))
    list_bug = list(set_bug)
    list_bug.sort()
    _file, _line = dic_target[fuzz_id][0].split(":")
    _list_target = []
    if _line.find("-") > 0:
        for line in range(int(_line.split("-")[0]), int(_line.split("-")[1]) + 1):
            _list_target.append(_file + ":" + str(line))
    elif _line.find("|") > 0:
        for line in _line.split("|"):
            _list_target.append(_file + ":" + str(line))
    else:
        _list_target.append(_file + ":" + str(_line))

    for bug_line in list_bug:
        _flag = False
        _bug_line = bug_line.split()[0].split("/")[-1]
        _bug_type = bug_line.split()[1]
        for target in _list_target:
            if _bug_line.find(target) >= 0:
                _flag = True
                break
        # if (_flag == False):
        #     continue

        print(_bug_line + "|" + _bug_type + "||", end=" "),
        for _ in range(1, list_idx[-1] + 1):
            if _ in dict_asan and bug_line in dict_asan[_]:
                print(dict_asan[_][bug_line], end=" "),
            else:
                print("x", end=" ")
        print("")


if __name__ == "__main__":
    dirpath = sys.argv[1]

    # path_target = "dfuzz_target.json"
    path_target = ""
    if os.path.exists(path_target):
        f = open(path_target)
        dic_target = json.loads(f.read())[0]
    else:
        dic_target = dict()

    # try:
    if os.path.isdir(dirpath):
        for fuzz_id in id_list:
            parse_dir(dirpath, fuzz_id)
            print("")
    else:
        dict_bug_time = parse_log(dirpath)
        asan_folder = Path(dirpath).parent
        for _ in dict_bug_time:
            print(f"{_}: {int(dict_bug_time[_]['time'])}")
            md5_hash = hashlib.md5(_.encode()).hexdigest()
            asan_report = asan_folder / f"{md5_hash}.log"
            asan_report.write_text(
                dict_bug_time[_]["seed"]
                + "\n"
                + _
                + "\n"
                + "".join(dict_bug_time[_]["report"])
            )
