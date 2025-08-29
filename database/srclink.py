#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Create soft link for all files in the source directory to the target directory,
with the same directory structure.
Used by build.sh in database.
"""

import sys
from pathlib import Path

def create_soft_link(src: Path, dst: Path):
    for file in src.rglob("*"):
        if file.is_file():
            target = dst / file.relative_to(src)
            target.parent.mkdir(parents=True, exist_ok=True)
            target.symlink_to(file.resolve())

def main():
    if len(sys.argv) != 3:
        print("Usage: srclink.py <src> <dst>")
        sys.exit(1)

    src = Path(sys.argv[1])
    dst = Path(sys.argv[2])
    create_soft_link(src, dst)

if __name__ == "__main__":
    main()