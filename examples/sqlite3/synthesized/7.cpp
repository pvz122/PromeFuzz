// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_name at sqlite3.c:78913:24 in sqlite3.h
// sqlite3_stricmp at sqlite3.c:22070:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:78800:16 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    sqlite3_str *str;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a simple table and insert a row
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, name TEXT);";
    if (sqlite3_exec(db, create_table_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    const char *insert_sql = "INSERT INTO test (id, name) VALUES (1, 'test');";
    if (sqlite3_exec(db, insert_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare a SELECT statement
    const char *select_sql = "SELECT * FROM test;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the statement to get the first row
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call sqlite3_column_name
        const char *column_name = sqlite3_column_name(stmt, 0);
        if (column_name) {
            // Call sqlite3_stricmp
            sqlite3_stricmp(column_name, "id");

            // Call sqlite3_column_type
            sqlite3_column_type(stmt, 0);
        }
    }

    // Create a new sqlite3_str object
    str = sqlite3_str_new(db);
    if (!str) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Call sqlite3_str_appendf
    sqlite3_str_appendf(str, "Test string: %s", "fuzz");

    // Call sqlite3_str_appendf again
    sqlite3_str_appendf(str, " with size: %d", (int)Size);

    // Finalize the prepared statement
    sqlite3_finalize(stmt);

    // Call sqlite3_str_appendf one more time
    sqlite3_str_appendf(str, " after finalize");

    // Call sqlite3_str_finish
    char *result = sqlite3_str_finish(str);
    if (result) {
        sqlite3_free(result);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}