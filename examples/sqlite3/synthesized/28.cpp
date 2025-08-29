// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_complete at sqlite3.c:167429:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize sqlite3 database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare input data
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // Call sqlite3_mprintf
    char *mprintf_result = sqlite3_mprintf("%s", sql);
    if (!mprintf_result) {
        free(sql);
        sqlite3_close(db);
        return 0;
    }

    // Call sqlite3_complete
    sqlite3_complete(mprintf_result);

    // Call sqlite3_exec
    char *errmsg = nullptr;
    sqlite3_exec(db, mprintf_result, nullptr, nullptr, &errmsg);

    // Call sqlite3_free
    sqlite3_free(mprintf_result);

    // Call sqlite3_free again
    if (errmsg) {
        sqlite3_free(errmsg);
    }

    // Call sqlite3_exec again
    sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);

    // Call sqlite3_close
    sqlite3_close(db);

    // Cleanup
    free(sql);
    if (errmsg) {
        sqlite3_free(errmsg);
    }

    return 0;
}