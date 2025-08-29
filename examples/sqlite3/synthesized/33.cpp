// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:79129:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:79132:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:79118:16 in sqlite3.h
// sqlite3_bind_text64 at sqlite3.c:79181:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:79129:16 in sqlite3.h
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
#include <stdint.h>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) + sizeof(sqlite3_int64) + sizeof(double) + sizeof(sqlite3_uint64) + sizeof(int)) {
        return 0;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER, value REAL, text TEXT);";
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    int param_index = 1;
    int int_value = *reinterpret_cast<const int*>(Data);
    sqlite3_bind_int(stmt, param_index++, int_value);

    sqlite3_int64 int64_value = *reinterpret_cast<const sqlite3_int64*>(Data + sizeof(int));
    sqlite3_bind_int64(stmt, param_index++, int64_value);

    double double_value = *reinterpret_cast<const double*>(Data + sizeof(int) + sizeof(sqlite3_int64));
    sqlite3_bind_double(stmt, param_index++, double_value);

    const char *text_value = reinterpret_cast<const char*>(Data + sizeof(int) + sizeof(sqlite3_int64) + sizeof(double));
    sqlite3_uint64 text_length = *reinterpret_cast<const sqlite3_uint64*>(Data + sizeof(int) + sizeof(sqlite3_int64) + sizeof(double));
    sqlite3_bind_text64(stmt, param_index++, text_value, text_length, SQLITE_TRANSIENT, SQLITE_UTF8);

    int int_value2 = *reinterpret_cast<const int*>(Data + sizeof(int) + sizeof(sqlite3_int64) + sizeof(double) + sizeof(sqlite3_uint64));
    sqlite3_bind_int(stmt, param_index, int_value2);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}