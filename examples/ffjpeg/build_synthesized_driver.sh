#! /bin/bash

cd /promefuzz
clang /promefuzz/database/ffjpeg/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/ffjpeg/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/ffjpeg/latest/code/src database/ffjpeg/latest/bin_asan/lib/libffjpeg.a
