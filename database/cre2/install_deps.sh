#!/bin/bash

DEPS="texinfo autoconf libtool"
if [ "$EUID" -eq 0 ]; then
    apt install $DEPS
else
    sudo apt install $DEPS
fi

# libabsl must be installed muanually
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
cp ../disable_abseil_debug.patch .
git apply disable_abseil_debug.patch
mkdir build && cd build
cmake ../ -DCMAKE_INSTALL_PREFIX=../bin
make -j12 && make install
