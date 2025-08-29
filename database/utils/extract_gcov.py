import sys
import json
from pathlib import Path

print("e.g., python utils/extract_gcov.py ./tinygltf/latest/gcov ossfuzz")

workdir = Path(sys.argv[1])
fuzz_id = sys.argv[2]


list_cov_dir = []
for dir in workdir.glob(f"{fuzz_id}_*"):
    list_cov_dir.append(dir)
list_cov_dir.sort()

list_line = []
list_br = []
for cov_dir in list_cov_dir:
    cov_file = Path(cov_dir) / "gcov-24.json"
    if not cov_file.exists():
        continue
    dict_cov = json.loads(cov_file.read_text())
    list_line.append(dict_cov["Summary"]["line"])
    list_br.append(dict_cov["Summary"]["branch"])


print(" ".join(str(item) for item in list_line))
print(" ".join(str(item) for item in list_br))