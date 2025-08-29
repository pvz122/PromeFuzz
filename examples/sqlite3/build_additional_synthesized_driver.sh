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
AFL_LLVM_USE_TRACE_PC=1 AFL_USE_ASAN=1 $AFLPP_PATH/afl-clang-fast++ /promefuzz/database/sqlite3/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/sqlite3/latest/out/fuzz_driver/aflpp_synthesized_driver $AFLPP_LIB_PATH -g -I/promefuzz/database/sqlite3/latest/code database/sqlite3/latest/bin_aflpp/lib/libsqlite3.a -DSQLITE_MAX_LENGTH=128000000 -DSQLITE_MAX_SQL_LENGTH=128000000 -DSQLITE_MAX_MEMORY=25000000 -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 -DSQLITE_DEBUG=1 -DSQLITE_MAX_PAGE_COUNT=16384 -DSQLITE_ALLOW_URI_AUTHORITY -DSQLITE_ENABLE_API_ARMOR -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_ENABLE_NORMALIZE -DSQLITE_ENABLE_PREUPDATE_HOOK -DSQLITE_ENABLE_SNAPSHOT -DSQLITE_ENABLE_STMT_SCANSTATUS -DSQLITE_ENABLE_UNLOCK_NOTIFY
# gcov
clang++ /promefuzz/database/sqlite3/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/sqlite3/latest/out/fuzz_driver/gcov_synthesized_driver --coverage -fsanitize=fuzzer -g -I/promefuzz/database/sqlite3/latest/code database/sqlite3/latest/bin_gcov/lib/libsqlite3.a -DSQLITE_MAX_LENGTH=128000000 -DSQLITE_MAX_SQL_LENGTH=128000000 -DSQLITE_MAX_MEMORY=25000000 -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 -DSQLITE_DEBUG=1 -DSQLITE_MAX_PAGE_COUNT=16384 -DSQLITE_ALLOW_URI_AUTHORITY -DSQLITE_ENABLE_API_ARMOR -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_ENABLE_NORMALIZE -DSQLITE_ENABLE_PREUPDATE_HOOK -DSQLITE_ENABLE_SNAPSHOT -DSQLITE_ENABLE_STMT_SCANSTATUS -DSQLITE_ENABLE_UNLOCK_NOTIFY
# cov
clang++ /promefuzz/database/sqlite3/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/sqlite3/latest/out/fuzz_driver/cov_synthesized_driver -fprofile-instr-generate -fcoverage-mapping -fsanitize=fuzzer -g -I/promefuzz/database/sqlite3/latest/code database/sqlite3/latest/bin_cov/lib/libsqlite3.a -DSQLITE_MAX_LENGTH=128000000 -DSQLITE_MAX_SQL_LENGTH=128000000 -DSQLITE_MAX_MEMORY=25000000 -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 -DSQLITE_DEBUG=1 -DSQLITE_MAX_PAGE_COUNT=16384 -DSQLITE_ALLOW_URI_AUTHORITY -DSQLITE_ENABLE_API_ARMOR -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_ENABLE_NORMALIZE -DSQLITE_ENABLE_PREUPDATE_HOOK -DSQLITE_ENABLE_SNAPSHOT -DSQLITE_ENABLE_STMT_SCANSTATUS -DSQLITE_ENABLE_UNLOCK_NOTIFY