// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:77509:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:168857:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:79172:16 in sqlite3.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_reset(stmt);
    int changes = sqlite3_changes(db);

    const char *text = reinterpret_cast<const char*>(Data);
    int text_len = static_cast<int>(Size);
    sqlite3_bind_text(stmt, 1, text, text_len, SQLITE_TRANSIENT);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}