#! /bin/bash

cd /promefuzz
clang /promefuzz/database/libtiff/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libtiff/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libtiff/latest/code/libtiff -Idatabase/libtiff/latest/bin_asan/include database/libtiff/latest/bin_asan/lib/libtiff.a database/libtiff/latest/bin_asan/lib/libtiffxx.a -lz -ljpeg -ljbig -llzma -lzstd
