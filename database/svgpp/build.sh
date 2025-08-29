#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

bear -- $CXX -g -c ../code/svgpp.cpp -I ../code/include -o svgpp.o || exit 1
cp -r ../code/include ./ || exit 1

popd

echo "end compiling $PWD with $MODE"