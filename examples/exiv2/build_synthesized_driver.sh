#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/exiv2/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/exiv2/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/exiv2/latest/code/include/exiv2 database/exiv2/latest/bin_asan/lib/libexiv2.a -Idatabase/exiv2/latest/code/include -Idatabase/exiv2/latest/build_asan -lfmt -lexpat -lz -lINIReader
