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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast /promefuzz/database/zlib/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/zlib/latest/out/fuzz_driver/aflpp_synthesized_driver $AFLPP_LIB_PATH -g -I/promefuzz/database/zlib/latest/code database/zlib/latest/build_aflpp/libz.a -DHAVE_HIDDEN -DNO_FSEEKO -DZLIB_BUILD -DZLIB_DLL -D_LARGEFILE64_SOURCE=1
# gcov
clang /promefuzz/database/zlib/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/zlib/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/zlib/latest/code database/zlib/latest/build_gcov/libz.a -DHAVE_HIDDEN -DNO_FSEEKO -DZLIB_BUILD -DZLIB_DLL -D_LARGEFILE64_SOURCE=1
# cov
clang /promefuzz/database/zlib/latest/out/fuzz_driver/synthesized/*.c -o /promefuzz/database/zlib/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/zlib/latest/code database/zlib/latest/build_cov/libz.a -DHAVE_HIDDEN -DNO_FSEEKO -DZLIB_BUILD -DZLIB_DLL -D_LARGEFILE64_SOURCE=1