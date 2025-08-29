#! /bin/bash

rm -r build
mkdir -p build
pushd build
cmake ../
make || exit 1
popd
./build/bin/preprocessor processor/cxx/example/example.cpp -o processor/cxx/example/example.json &> /dev/null || (echo "Test failed" && exit 1)