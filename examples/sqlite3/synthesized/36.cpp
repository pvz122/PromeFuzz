// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_db_handle at sqlite3.c:79362:21 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:78629:16 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:79278:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM dummy_table";

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3 *db_handle = sqlite3_db_handle(stmt);
    if (db_handle == nullptr) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    int column_count = sqlite3_column_count(stmt);
    int bind_parameter_count = sqlite3_bind_parameter_count(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}