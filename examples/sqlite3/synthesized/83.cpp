// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:129962:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:77530:16 in sqlite3.h
// sqlite3_stmt_readonly at sqlite3.c:79370:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    // Ensure the input is at least 2 bytes and even (UTF-16 requires even size)
    if (Size < 2 || (Size % 2 != 0)) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const void *pzTail;

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement using the input data
    int rc = sqlite3_prepare16_v3(db, Data, Size, 0, &stmt, &pzTail);
    if (rc == SQLITE_OK) {
        // Clear bindings if the statement is prepared successfully
        sqlite3_clear_bindings(stmt);

        // Check if the statement is read-only
        sqlite3_stmt_readonly(stmt);

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}