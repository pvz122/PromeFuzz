#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/libjpeg-turbo/latest/code/src database/libjpeg-turbo/latest/bin_asan/lib/libturbojpeg.a -Idatabase/libjpeg-turbo/latest/build_asan
