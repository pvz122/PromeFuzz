// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare at sqlite3.c:129810:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_parameter_index at sqlite3.c:79304:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:78629:16 in sqlite3.h
// sqlite3_column_decltype at sqlite3.c:78936:24 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:79278:16 in sqlite3.h
// sqlite3_bind_parameter_name at sqlite3.c:79289:24 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_159(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *tail;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement with the input data
    const char *sql = reinterpret_cast<const char *>(Data);
    int sql_len = Size;
    if (sqlite3_prepare(db, sql, sql_len, &stmt, &tail) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzz sqlite3_bind_parameter_index
    const char *param_name = "param";
    sqlite3_bind_parameter_index(stmt, param_name);

    // Fuzz sqlite3_column_decltype
    int col_count = sqlite3_column_count(stmt);
    for (int i = 0; i < col_count; ++i) {
        sqlite3_column_decltype(stmt, i);
    }

    // Fuzz sqlite3_bind_parameter_name
    int param_count = sqlite3_bind_parameter_count(stmt);
    for (int i = 1; i <= param_count; ++i) {
        sqlite3_bind_parameter_name(stmt, i);
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}