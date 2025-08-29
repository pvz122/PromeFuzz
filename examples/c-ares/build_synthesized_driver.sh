#! /bin/bash

cd /promefuzz
clang /promefuzz/database/c-ares/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/c-ares/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/c-ares/latest/code/include database/c-ares/latest/bin_asan/lib/libcares.so -Idatabase/c-ares/latest/build_asan
