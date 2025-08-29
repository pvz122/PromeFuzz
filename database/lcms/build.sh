#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

../code/configure --prefix=$PWD/../bin_$MODE --enable-static --disable-shared
if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi

make install || exit 1

popd

echo "end compiling $PWD with $MODE"