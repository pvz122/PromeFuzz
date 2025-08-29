// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:79118:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_get_table at sqlite3.c:138893:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_free_table at sqlite3.c:138962:17 in sqlite3.h
// sqlite3_table_column_metadata at sqlite3.c:171666:16 in sqlite3.h
// sqlite3_result_error at sqlite3.c:77859:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errmsg = nullptr;
    char **result = nullptr;
    int nRow, nColumn;
    const char *dataType, *collSeq;
    int notNull, primaryKey, autoinc;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table for testing
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value REAL);";
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement for binding
    const char *insertSQL = "INSERT INTO test (value) VALUES (?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind a double value to the statement
    double value;
    memcpy(&value, Data, sizeof(double));
    sqlite3_bind_double(stmt, 1, value);

    // Execute the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Test sqlite3_errmsg
    const char *errMsg = sqlite3_errmsg(db);

    // Test sqlite3_get_table
    const char *selectSQL = "SELECT * FROM test;";
    sqlite3_get_table(db, selectSQL, &result, &nRow, &nColumn, &errmsg);
    if (errmsg) {
        sqlite3_free(errmsg);
    }
    if (result) {
        sqlite3_free_table(result);
    }

    // Test sqlite3_table_column_metadata
    sqlite3_table_column_metadata(db, "main", "test", "value", &dataType, &collSeq, &notNull, &primaryKey, &autoinc);

    // Test sqlite3_result_error
    sqlite3_context *ctx = nullptr;
    sqlite3_result_error(ctx, "Test error", -1);

    // Clean up
    sqlite3_close(db);

    return 0;
}