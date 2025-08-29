#! /bin/bash

cd /promefuzz
clang /promefuzz/database/ngiflib/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/ngiflib/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -I/promefuzz/database/ngiflib/latest/build_asan ./database/ngiflib/latest/bin_asan/lib/libngiflib.a -lSDL -I/usr/include/SDL
