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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast++ /promefuzz/database/lcms/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/lcms/latest/out/fuzz_driver/aflpp_synthesized_driver -fsanitize=fuzzer -g -I/promefuzz/database/lcms/latest/code/include database/lcms/latest/bin_aflpp/lib/liblcms2.a
# gcov
clang++ /promefuzz/database/lcms/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/lcms/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/lcms/latest/code/include database/lcms/latest/bin_gcov/lib/liblcms2.a
# cov
clang++ /promefuzz/database/lcms/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/lcms/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/lcms/latest/code/include database/lcms/latest/bin_cov/lib/liblcms2.a