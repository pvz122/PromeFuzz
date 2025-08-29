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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast++ /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/aflpp_synthesized_driver $AFLPP_LIB_PATH -g -I/promefuzz/database/libjpeg-turbo/latest/code/src database/libjpeg-turbo/latest/bin_aflpp/lib/libturbojpeg.a -Idatabase/libjpeg-turbo/latest/build_aflpp
# gcov
clang++ /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/libjpeg-turbo/latest/code/src database/libjpeg-turbo/latest/bin_gcov/lib/libturbojpeg.a -Idatabase/libjpeg-turbo/latest/build_gcov
# cov
clang++ /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/libjpeg-turbo/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/libjpeg-turbo/latest/code/src database/libjpeg-turbo/latest/bin_cov/lib/libturbojpeg.a -Idatabase/libjpeg-turbo/latest/build_cov