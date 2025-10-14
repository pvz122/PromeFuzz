#! /bin/bash
if [ -z "$AFLPP_PATH" ]; then
    AFL_CLANG_FAST_PATH=$(command -v afl-clang-fast)
    if [ -z "$AFL_CLANG_FAST_PATH" ]; then
        echo "Please install AFL++ and set AFLPP_PATH" && exit 1
    fi
    AFLPP_PATH=$(dirname "$AFL_CLANG_FAST_PATH")
fi
cd /promefuzz
# aflpp
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast /promefuzz/database/libtiff/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libtiff/latest/out/fuzz_driver/aflpp_synthesized_driver -fsanitize=fuzzer -g -I/promefuzz/database/libtiff/latest/code/libtiff -Idatabase/libtiff/latest/bin_aflpp/include database/libtiff/latest/bin_aflpp/lib/libtiff.a database/libtiff/latest/bin_aflpp/lib/libtiffxx.a -lz -ljpeg -ljbig -llzma -lzstd
# gcov
clang /promefuzz/database/libtiff/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libtiff/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/libtiff/latest/code/libtiff -Idatabase/libtiff/latest/bin_gcov/include database/libtiff/latest/bin_gcov/lib/libtiff.a database/libtiff/latest/bin_gcov/lib/libtiffxx.a -lz -ljpeg -ljbig -llzma -lzstd
# cov
clang /promefuzz/database/libtiff/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/libtiff/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/libtiff/latest/code/libtiff -Idatabase/libtiff/latest/bin_cov/include database/libtiff/latest/bin_cov/lib/libtiff.a database/libtiff/latest/bin_cov/lib/libtiffxx.a -lz -ljpeg -ljbig -llzma -lzstd