// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_str_append at sqlite3.c:18884:17 in sqlite3.h
// sqlite3_str_append at sqlite3.c:18884:17 in sqlite3.h
// sqlite3_str_value at sqlite3.c:18984:18 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <sqlite3.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_str *str = sqlite3_str_new(db);
    if (!str) {
        sqlite3_close(db);
        return 0;
    }

    const char *input = reinterpret_cast<const char*>(Data);
    int input_len = static_cast<int>(Size);

    sqlite3_str_append(str, input, input_len);
    sqlite3_str_append(str, input, input_len);

    sqlite3_stmt *stmt;
    const char *tail;
    const char *sql = sqlite3_str_value(str);
    if (sql) {
        sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
        sqlite3_finalize(stmt);
    }

    char *result = sqlite3_str_finish(str);
    if (result) {
        sqlite3_free(result);
    }

    sqlite3_close(db);

    return 0;
}