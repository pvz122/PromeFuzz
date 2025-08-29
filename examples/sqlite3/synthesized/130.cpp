// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_initialize at sqlite3.c:167905:16 in sqlite3.h
// sqlite3_global_recover at sqlite3.c:171582:16 in sqlite3.h
// sqlite3_release_memory at sqlite3.c:16912:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_limit at sqlite3.c:170661:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_db_release_memory at sqlite3.c:168612:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:168087:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *Data, size_t Size) {
    // Initialize SQLite
    sqlite3_initialize();

    // Fuzz sqlite3_global_recover
    sqlite3_global_recover();

    // Fuzz sqlite3_release_memory
    int bytes_to_free = static_cast<int>(Size);
    sqlite3_release_memory(bytes_to_free);

    // Fuzz sqlite3_limit
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
        int limit_id = static_cast<int>(Data[0] % 10); // Use a fixed number of limit categories
        int new_limit = static_cast<int>(Size);
        sqlite3_limit(db, limit_id, new_limit);
        sqlite3_close(db);
    }

    // Fuzz sqlite3_db_release_memory
    if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
        sqlite3_db_release_memory(db);
        sqlite3_close(db);
    }

    // Fuzz sqlite3_shutdown
    sqlite3_shutdown();

    return 0;
}