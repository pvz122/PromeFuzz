#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
import os
import sys
from pathlib import Path


def replace_sqlite3_header_content(file_path: Path):
    """
    Replaces the embedded sqlite3.h content in a file with #include "sqlite3.h".

    The script looks for the start and end markers:
    /************** Begin file sqlite3.h *****************************************
    ...
    /************** End of sqlite3.h ***********************************************

    and replaces the content between them (inclusive of the markers) with a
    single line: #include "sqlite3.h"

    Args:
        file_path (str): The path to the file to modify.
    """
    lines = file_path.read_text(encoding="utf-8").splitlines()
    lines_iter = iter(lines)
    new_lines = []
    for line in lines_iter:
        if line.startswith("/************** Begin file sqlite3.h"):
            new_lines.append('#include "sqlite3.h"')
            # Skip all lines until we find the end marker
            while line is not None and not line.startswith("/************** End of sqlite3.h"):
                line = next(lines_iter, None)
            continue
        if line.startswith("/************** Begin file sqlite3ext.h"):
            new_lines.append('#include "sqlite3ext.h"')
            # Skip all lines until we find the end marker
            while line is not None and not line.startswith("/************** End of sqlite3ext.h"):
                line = next(lines_iter, None)
            continue
        if line.startswith("SQLITE_API const char sqlite3_version[] = SQLITE_VERSION;"):
            new_lines[-4] = f"// {new_lines[-4]}"
            new_lines.append(line)
            line = next(lines_iter, None)
            new_lines.append(f"// {line}")
            line = next(lines_iter, None)
        new_lines.append(line)
    file_path.write_text("\n".join(new_lines), encoding="utf-8")


if __name__ == "__main__":
    # The user's current file is the one to be modified.
    # You can change this path if needed.
    target_file = Path(sys.argv[1])
    if not target_file.exists():
        print(f"The target file does not exist: {target_file}")
        sys.exit(1)

    if os.path.exists(target_file):
        replace_sqlite3_header_content(target_file)
    else:
        print(f"The target file does not exist: {target_file}")
