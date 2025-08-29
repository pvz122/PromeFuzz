#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/loguru/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/loguru/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/loguru/latest/code database/loguru/latest/bin_asan/lib/libloguru.a
