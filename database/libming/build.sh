#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

CFLAGS+=" -fcommon"
if [[ $MODE == "aflpp" ]]; then
    export AFL_USE_ASAN=0
    CFLAGS+=" -fsanitize=address"
fi
export CFLAGS=$CFLAGS

# ./autogen.sh
../code/configure --prefix=$PWD/../bin_$MODE --enable-static --disable-shared --disable-freetype
# parallel calls to bison will cause error: 
# https://github.com/libming/libming/issues/49
if [[ $MODE == "asan" ]]; then
    bear -- make || exit 1
else
    make || exit 1
fi

make install

popd

echo "end compiling $PWD with $MODE"