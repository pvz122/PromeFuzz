#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
mkdir build_$MODE/re2
mkdir build_$MODE/cre2

# build re2
pushd build_$MODE/re2
cmake ../../code/re2 -DCMAKE_INSTALL_PREFIX=$PWD/../../bin_$MODE/re2 -DCMAKE_PREFIX_PATH=$PWD/../../../abseil-cpp/bin
if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi
make install || exit 1
popd

# build cre2
pushd build_$MODE/cre2
PKG_CONFIG_PATH=$PWD/../../bin_$MODE/re2/lib/pkgconfig:$PWD/../../../abseil-cpp/bin/lib/pkgconfig ../../code/cre2/configure --enable-maintainer-mode --prefix=$PWD/../../bin_$MODE/cre2 --enable-static --disable-shared
if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi
make install || exit 1
popd

echo "end compiling $PWD with $MODE"