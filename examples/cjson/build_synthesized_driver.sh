#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/cjson/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/cjson/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/cjson/latest/code database/cjson/latest/bin_asan/lib/libcjson.a
