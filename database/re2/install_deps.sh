#!/bin/bash

# sudo apt install libabsl-dev
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
cp ../disable_abseil_debug.patch .
git apply disable_abseil_debug.patch
mkdir build && cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../bin
make -j12 && make install