#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
../../srclink.py code build_$MODE || ( echo "[ERROR]: No code folder find!" && exit 1 )
pushd build_$MODE

if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi

ar cru libngiflib.a *.o

popd
mkdir -p bin_$MODE/bin
cp build_$MODE/gif2tga bin_$MODE/bin
cp build_$MODE/SDLaffgif bin_$MODE/bin
mkdir -p bin_$MODE/include
cp build_$MODE/*.h bin_$MODE/include
mkdir -p bin_$MODE/lib
cp build_$MODE/libngiflib.a bin_$MODE/lib

echo "end compiling $PWD with $MODE"