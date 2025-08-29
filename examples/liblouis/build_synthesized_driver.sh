#! /bin/bash

cd /promefuzz
clang /promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/liblouis/latest/build_asan/liblouis database/liblouis/latest/bin_asan/lib/liblouis.a -lyaml
