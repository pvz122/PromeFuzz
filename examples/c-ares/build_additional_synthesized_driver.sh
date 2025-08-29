#! /bin/bash
if [ -z "$AFLPP_PATH" ]; then
    AFL_CLANG_FAST_PATH=$(command -v afl-clang-fast)
    if [ -z "$AFL_CLANG_FAST_PATH" ]; then
        echo "Please install AFL++ and set AFLPP_PATH" && exit 1
    fi
    AFLPP_PATH=$(dirname "$AFL_CLANG_FAST_PATH")
    AFLPP_LIB_PATH=$(dirname "$AFLPP_PATH")/lib/afl/libAFLDriver.a
else
    AFLPP_LIB_PATH=$AFLPP_LIB_PATH
fi
cd /promefuzz
# aflpp
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast /promefuzz/database/c-ares/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/c-ares/latest/out/fuzz_driver/aflpp_synthesized_driver $AFLPP_LIB_PATH -g -I/promefuzz/database/c-ares/latest/code/include database/c-ares/latest/bin_aflpp/lib/libcares.so -Idatabase/c-ares/latest/build_aflpp
# gcov
clang /promefuzz/database/c-ares/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/c-ares/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/c-ares/latest/code/include database/c-ares/latest/bin_gcov/lib/libcares.so -Idatabase/c-ares/latest/build_gcov
# cov
clang /promefuzz/database/c-ares/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/c-ares/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/c-ares/latest/code/include database/c-ares/latest/bin_cov/lib/libcares.so -Idatabase/c-ares/latest/build_cov