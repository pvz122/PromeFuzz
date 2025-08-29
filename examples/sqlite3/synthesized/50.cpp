// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:79096:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_value_blob at sqlite3.c:77563:24 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_value *value = sqlite3_column_value(stmt, 0);
        const void *blob = sqlite3_value_blob(value);
        // Avoid calling sqlite3_value_text16be, sqlite3_value_text16le, and sqlite3_value_text16
        // as they require a protected sqlite3_value object.
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}