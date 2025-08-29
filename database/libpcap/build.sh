#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

cmake ../code -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$PWD/../bin_$MODE

if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi


make install || exit 1

# make documents
find $PWD/../bin_$MODE/share/man -type f | xargs groff -mandoc -Tascii -rLL=9999n -P-c | col -b | sed -E '/^[-=]+\t*$/d; s/\t+//g' > $PWD/mandoc.txt

popd

echo "end compiling $PWD with $MODE"