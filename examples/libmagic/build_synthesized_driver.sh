#! /bin/bash

cd /promefuzz
clang /promefuzz/database/libmagic/latest/out-ori/fuzz_driver/synthesized/*.c -o /promefuzz/database/libmagic/latest/out-ori/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libmagic/latest/build_asan/src database/libmagic/latest/bin_asan/lib/libmagic.a -llzma -lzstd -lz
