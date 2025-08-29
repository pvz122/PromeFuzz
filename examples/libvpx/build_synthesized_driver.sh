#! /bin/bash

cd /promefuzz
clang /promefuzz/database/libvpx/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libvpx/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libvpx/latest/code/vpx database/libvpx/latest/bin_asan/lib/libvpx.a -Idatabase/libvpx/latest/code
