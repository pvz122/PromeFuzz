#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/curl/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/curl/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/curl/latest/code/include/curl database/curl/latest/bin_asan/lib/libcurl.a -Idatabase/curl/latest/code/include -lpsl -lzstd -lz -lcrypto -lssl
