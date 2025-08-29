#! /usr/bin/env python3
# -*- coding: utf-8 -*-
"""
The tinygltf library is a single-header library.
Inside the header, there is a macro named `TINYGLTF_IMPLEMENTATION`.
If it is defined, the implementation of the library is included in the header.
If it is not defined, only the declaration is included.
This will cause tricky problems when extracting the API functions from the header.
The solution is to separate the declaration and implementation, and
move the implementation to the source file.
"""

import sys
from pathlib import Path

gltf_dir = Path(sys.argv[1])
gltf_header = gltf_dir / "tiny_gltf.h"
gltf_src = gltf_dir / "tiny_gltf.cc"

gltf_decl, gltf_impl = gltf_header.read_text().split(
    "#if defined(TINYGLTF_IMPLEMENTATION)"
)
with gltf_header.open("w") as f:
    f.write(gltf_decl)
with gltf_src.open("a") as f:
    f.write("#if defined(TINYGLTF_IMPLEMENTATION)" + gltf_impl)
