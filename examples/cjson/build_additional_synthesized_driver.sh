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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast++ /promefuzz/database/cjson/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/cjson/latest/out/fuzz_driver/aflpp_synthesized_driver -fsanitize=fuzzer -g -I/promefuzz/database/cjson/latest/code database/cjson/latest/bin_aflpp/lib/libcjson.a
# gcov
clang++ /promefuzz/database/cjson/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/cjson/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/cjson/latest/code database/cjson/latest/bin_gcov/lib/libcjson.a
# cov
clang++ /promefuzz/database/cjson/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/cjson/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/cjson/latest/code database/cjson/latest/bin_cov/lib/libcjson.a