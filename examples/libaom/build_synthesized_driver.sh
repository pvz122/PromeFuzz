#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/libaom/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/libaom/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libaom/latest/code/aom database/libaom/latest/bin_asan/lib/libaom.a -Idatabase/libaom/latest/code -Idatabase/libaom/latest/code/aom
