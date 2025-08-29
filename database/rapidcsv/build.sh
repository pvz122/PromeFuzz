#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
../../srclink.py code build_$MODE
pushd build_$MODE

if [[ $MODE == "asan" ]]; then
    bear -- $CXX $CXXFLAGS -c src/rapidcsv.cpp -o rapidcsv.o || exit 1
else
    $CXX $CXXFLAGS -c src/rapidcsv.cpp -o rapidcsv.o || exit 1
fi

popd
mkdir -p bin_$MODE/include
cp build_$MODE/src/rapidcsv.h bin_$MODE/include

echo "end compiling $PWD with $MODE"