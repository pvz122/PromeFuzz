import os
import sys
import tomllib
from pathlib import Path
from loguru import logger


# for afl res
class Extraction:
    def __init__(self, project_name: str, path_base: str, afltype, lognum=1):
        self.flag_print = False
        self.project_name = project_name
        self.afltype = afltype
        self.dict_id_time = dict()

        if afltype == "aflpp":
            self.path = "%s/out/default" % (path_base)
        else:
            self.path = "%s/out" % (path_base)
        self.lognum = lognum

    def _need_rename(self) -> bool:
        if self.project_name in ["liblouis"]:
            return True
        else:
            return False

    def extract(self, target_time, target_type) -> list[str]:
        """
        Extract crashes or queue files from AFL-based fuzzer

        :param target_time: seconds
        :param target_type: "crashes" or "queue"
        :return: file (str) list
        """
        l = []
        self.target_type = target_type
        if self.afltype.find("angora") >= 0 or self.afltype.find("parmesan") >= 0:
            l = self._extract_angora(target_time)
            return l

        if self.lognum == 1:
            base_path = self.path
            l = self._extract(target_time, base_path, self._need_rename())
        else:
            base_path = self.path + "/master"
            l = self._extract(target_time, base_path, self._need_rename())
            for i in range(1, self.lognum):
                l += self._extract(
                    target_time, self.path + f"/slave{i}", self._need_rename()
                )

        return l

    def _extract_angora(self, target_time):
        try:
            f = open("%s/angora.log" % (self.path), "rU")
        except:
            return []
        last_num = -1
        max_id = 0
        line = f.readline()
        while line:
            time = int(line.split(",")[0], 10)
            if time > target_time:
                break
            if self.target_type == "crashes":
                max_id = int(line.split(",")[4], 10) - 1
            elif self.target_type == "queue":
                max_id = int(line.split(",")[2], 10) - 1
            else:
                print("WRONG TYPE")
                exit(-1)
            if last_num != max_id:
                last_num = max_id
                self.dict_id_time[max_id] = time
                if self.flag_print:
                    print("%d: %d" % (time, max_id))
            line = f.readline()
        l = []
        for i in range(max_id):
            id = (6 - len(str(i))) * "0" + str(i)
            l.append(self.path + "/" + self.target_type + "/" + "id:" + id)
        l.sort()
        return l

    def _extract(self, target_time, target_path, rename):
        try:
            f_plot_data = open("%s/plot_data" % (target_path), "r")
        except:
            logger.warning(f"log not found in {target_path}/plot_data")
            return []
        line = f_plot_data.readline()
        line = f_plot_data.readline()
        is_first = True
        last_num = 0
        file_dict = {}
        seed_set = set()

        seed_parent_path = Path(f"{target_path}/{self.target_type}")
        for file in seed_parent_path.glob("id:*"):
            try:
                if file.name.find(":") >= 0:
                    id_str = file.name.split(":")[1].split(",")[0]
                    id = int(id_str, 10)
                else:
                    id = int(file)
            except:
                continue

            if rename == True:
                file = file.rename(file.parent / f"id:{id:06d}")

            file_dict[id] = str(file)
            # print(file_dict)
        num = 0
        while line:
            time = int(line.split(",")[0], 10)
            if self.target_type == "crashes":
                num = int(line.split(",")[7], 10)
            elif self.target_type == "queue":
                num = int(line.split(",")[3], 10)
            else:
                print("WRONG TYPE")
                exit(-1)
            if is_first == True:
                is_first = False
                if self.afltype.find("aflpp") >= 0:
                    first_time = 0
                else:
                    first_time = time

            if time - first_time > target_time:
                break
            if last_num != num:
                self.dict_id_time[num] = time - first_time
                if self.flag_print:
                    print("%d: %d" % (time - first_time, num - 1))
                last_num = num
            line = f_plot_data.readline()

        i = 0
        while i < num:
            try:
                seed_set.add(file_dict[i])
            except:
                print("??")
                i = i + 1
                pass
            i = i + 1

        ret = list(seed_set)
        ret.sort()
        return ret


if __name__ == "__main__":
    fuzz_time = 24

    project_name = "ngiflib"
    path_base = "ngiflib/latest/out_promefuzz_24_0"
    afltype = "aflpp"

    e = Extraction(project_name, path_base, afltype)  # path_base, fuzz_id, afltype
    e.flag_print = True
    seed_set = e.extract(3600 * float(fuzz_time), "crashes")  # hour
    print(len(seed_set))
    # print(len(seed_set))
