#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/tinygltf/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/tinygltf/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/tinygltf/latest/code database/tinygltf/latest/build_asan/libtinygltf.a
