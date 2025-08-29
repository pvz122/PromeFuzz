#! /bin/bash

cd /promefuzz
clang++ /promefuzz/database/sqlite3/latest/out/fuzz_driver/synthesized/*.cpp -o /promefuzz/database/sqlite3/latest/out/fuzz_driver/synthesized_driver -fsanitize=fuzzer,address,undefined -g -I/promefuzz/database/sqlite3/latest/code database/sqlite3/latest/bin_asan/lib/libsqlite3.a -DSQLITE_MAX_LENGTH=128000000 -DSQLITE_MAX_SQL_LENGTH=128000000 -DSQLITE_MAX_MEMORY=25000000 -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 -DSQLITE_DEBUG=1 -DSQLITE_MAX_PAGE_COUNT=16384 -DSQLITE_ALLOW_URI_AUTHORITY -DSQLITE_ENABLE_API_ARMOR -DSQLITE_ENABLE_COLUMN_METADATA -DSQLITE_ENABLE_NORMALIZE -DSQLITE_ENABLE_PREUPDATE_HOOK -DSQLITE_ENABLE_SNAPSHOT -DSQLITE_ENABLE_STMT_SCANSTATUS -DSQLITE_ENABLE_UNLOCK_NOTIFY
