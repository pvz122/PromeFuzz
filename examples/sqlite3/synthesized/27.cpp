// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:79129:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:79096:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_int at sqlite3.c:78769:16 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:78754:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
// sqlite3_column_int at sqlite3.c:78769:16 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19140:18 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19140:18 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:78754:16 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19140:18 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19140:18 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = nullptr;
    char buffer[256];

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *createTableSQL = "CREATE TABLE test (id INTEGER, data BLOB);";
    if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a statement to insert data
    const char *insertSQL = "INSERT INTO test (id, data) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the data
    sqlite3_bind_int(stmt, 1, 1);
    sqlite3_bind_blob(stmt, 2, Data, Size, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the insert statement
    sqlite3_finalize(stmt);

    // Prepare a statement to select data
    const char *selectSQL = "SELECT id, data FROM test;";
    if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the select statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the target API functions in the specified order
        sqlite3_column_int(stmt, 0);
        sqlite3_column_bytes(stmt, 1);
        sqlite3_column_blob(stmt, 1);
        sqlite3_snprintf(sizeof(buffer), buffer, "%d", sqlite3_column_int(stmt, 0));
        sqlite3_snprintf(sizeof(buffer), buffer, "%s", sqlite3_column_blob(stmt, 1));
        sqlite3_snprintf(sizeof(buffer), buffer, "%d", sqlite3_column_bytes(stmt, 1));
        sqlite3_snprintf(sizeof(buffer), buffer, "%p", sqlite3_column_blob(stmt, 1));
    }

    // Finalize the select statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}