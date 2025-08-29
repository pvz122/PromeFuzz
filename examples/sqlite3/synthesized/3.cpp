// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_test_control at sqlite3.c:171863:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17086:26 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17086:26 in sqlite3.h
// sqlite3_libversion at sqlite3.c:167813:24 in sqlite3.h
// sqlite3_sourceid at sqlite3.c:247679:24 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    char *errmsg = nullptr;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    // Call sqlite3_test_control with a valid operation code
    sqlite3_test_control(SQLITE_TESTCTRL_PRNG_SAVE, db);

    // Prepare SQL statement from fuzz input
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // First call to sqlite3_exec
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK && errmsg) {
        sqlite3_free(errmsg);
    }

    // Second call to sqlite3_exec
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK && errmsg) {
        sqlite3_free(errmsg);
    }

    // Close the database
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) return 0;

    // Call sqlite3_memory_used twice
    sqlite3_int64 mem_used1 = sqlite3_memory_used();
    sqlite3_int64 mem_used2 = sqlite3_memory_used();

    // Call sqlite3_libversion
    const char *lib_version = sqlite3_libversion();

    // Call sqlite3_sourceid
    const char *source_id = sqlite3_sourceid();

    free(sql);
    return 0;
}