// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:79278:16 in sqlite3.h
// sqlite3_bind_parameter_name at sqlite3.c:79289:24 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:79129:16 in sqlite3.h
// sqlite3_malloc64 at sqlite3.c:17232:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_bind_text64 at sqlite3.c:79181:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    int param_count = sqlite3_bind_parameter_count(stmt);
    if (param_count > 0) {
        const char *param_name = sqlite3_bind_parameter_name(stmt, 1);
        if (param_name != nullptr) {
            int value = 0;
            if (Size >= sizeof(int)) {
                value = *reinterpret_cast<const int*>(Data);
            }
            sqlite3_bind_int(stmt, 1, value);
        }
    }

    sqlite3_uint64 malloc_size = 0;
    if (Size >= sizeof(sqlite3_uint64)) {
        malloc_size = *reinterpret_cast<const sqlite3_uint64*>(Data);
    }
    void *ptr = sqlite3_malloc64(malloc_size);
    if (ptr != nullptr) {
        sqlite3_free(ptr);
    }

    const char *text = reinterpret_cast<const char*>(Data);
    sqlite3_uint64 text_size = Size;
    sqlite3_bind_text64(stmt, 1, text, text_size, SQLITE_TRANSIENT, SQLITE_UTF8);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}