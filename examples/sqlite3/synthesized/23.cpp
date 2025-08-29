// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_blob_open at sqlite3.c:89612:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_blob_reopen at sqlite3.c:89976:16 in sqlite3.h
// sqlite3_blob_bytes at sqlite3.c:89961:16 in sqlite3.h
// sqlite3_blob_close at sqlite3.c:89848:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_int64)) {
        return 0;
    }

    sqlite3 *db = nullptr;
    sqlite3_blob *blob = nullptr;
    sqlite3_int64 rowid = *reinterpret_cast<const sqlite3_int64*>(Data);

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a table with a BLOB column
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    if (sqlite3_exec(db, create_table_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert a row with a BLOB
    const char *insert_sql = "INSERT INTO test (data) VALUES (zeroblob(100));";
    if (sqlite3_exec(db, insert_sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Open a BLOB handle
    if (sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Invoke the target functions
    const char *err_msg = sqlite3_errmsg(db);
    int reopen_result = sqlite3_blob_reopen(blob, rowid);
    int blob_size = sqlite3_blob_bytes(blob);

    // Clean up
    sqlite3_blob_close(blob);
    sqlite3_close(db);

    return 0;
}