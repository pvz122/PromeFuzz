#!/bin/bash
. ../../common.sh $1

echo "start compiling $PWD with $MODE"

rm -rf build_$MODE bin_$MODE
mkdir build_$MODE
pushd build_$MODE

cmake ../code -DCMAKE_INSTALL_PREFIX=$PWD/../bin_$MODE -DBUILD_SHARED_LIBS=OFF -DEXIV2_ENABLE_SHARED=OFF -DEXIV2_ENABLE_BROTLI=OFF -DEXIV2_BUILD_DOC=ON
# ../code/configure --disable-shared --prefix=$PWD/../bin_$MODE
if [[ $MODE == "asan" ]]; then
    bear -- make -j$JOBS || exit 1
else
    make -j$JOBS || exit 1
fi

make doc
make install || exit 1

popd

echo "end compiling $PWD with $MODE"