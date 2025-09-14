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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast /promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/liblouis/latest/out/fuzz_driver/aflpp_synthesized_driver -fsanitize=fuzzer -g -I/promefuzz/database/liblouis/latest/build_aflpp/liblouis database/liblouis/latest/bin_aflpp/lib/liblouis.a -lyaml
# gcov
clang /promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/liblouis/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/liblouis/latest/build_gcov/liblouis database/liblouis/latest/bin_gcov/lib/liblouis.a -lyaml
# cov
clang /promefuzz/database/liblouis/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/liblouis/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/liblouis/latest/build_cov/liblouis database/liblouis/latest/bin_cov/lib/liblouis.a -lyaml