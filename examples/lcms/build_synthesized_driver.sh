#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/lcms/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/lcms/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/lcms/latest/code/include database/lcms/latest/bin_asan/lib/liblcms2.a
