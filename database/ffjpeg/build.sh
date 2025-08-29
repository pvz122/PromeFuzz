#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
../../srclink.py code build_$MODE
pushd build_$MODE

if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi

popd
mkdir -p bin_$MODE/bin
mkdir -p bin_$MODE/lib
mkdir -p bin_$MODE/include
cp build_$MODE/src/ffjpeg bin_$MODE/bin
cp build_$MODE/src/libffjpeg.a bin_$MODE/lib
cp build_$MODE/src/*.h bin_$MODE/include

echo "end compiling $PWD with $MODE"