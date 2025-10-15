#!/bin/bash

# sudo apt install libabsl-dev
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
# This version of abseil is compatible with re2 c84a140
git checkout 735c86164a69141f33ccfcb20ecf1b9254be32a7
cp ../disable_abseil_debug.patch .
git apply disable_abseil_debug.patch
mkdir build && cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../bin
make -j12 && make install