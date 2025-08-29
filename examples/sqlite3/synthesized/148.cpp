// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_sql at sqlite3.c:79485:24 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:79278:16 in sqlite3.h
// sqlite3_db_handle at sqlite3.c:79362:21 in sqlite3.h
// sqlite3_next_stmt at sqlite3.c:79432:26 in sqlite3.h
// sqlite3_column_count at sqlite3.c:78629:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement using the fuzz input as SQL
    sql = reinterpret_cast<const char*>(Data);
    if (sqlite3_prepare_v2(db, sql, Size, &stmt, nullptr) == SQLITE_OK) {
        // Test sqlite3_sql
        const char *sql_text = sqlite3_sql(stmt);
        if (sql_text) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test sqlite3_bind_parameter_count
        int param_count = sqlite3_bind_parameter_count(stmt);
        (void)param_count; // Suppress unused variable warning

        // Test sqlite3_db_handle
        sqlite3 *db_handle = sqlite3_db_handle(stmt);
        if (db_handle) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test sqlite3_next_stmt
        sqlite3_stmt *next_stmt = sqlite3_next_stmt(db, stmt);
        if (next_stmt) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test sqlite3_column_count
        int col_count = sqlite3_column_count(stmt);
        (void)col_count; // Suppress unused variable warning

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}