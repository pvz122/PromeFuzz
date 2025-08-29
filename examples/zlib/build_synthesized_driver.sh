#! /bin/bash

cd /promefuzz
clang /promefuzz/database/zlib/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/zlib/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/zlib/latest/code database/zlib/latest/build_asan/libz.a -DHAVE_HIDDEN -DNO_FSEEKO -DZLIB_BUILD -DZLIB_DLL -D_LARGEFILE64_SOURCE=1
