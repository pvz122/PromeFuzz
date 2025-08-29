// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_profile at sqlite3.c:170008:18 in sqlite3.h
// sqlite3_total_changes64 at sqlite3.c:168864:26 in sqlite3.h
// sqlite3_errmsg16 at sqlite3.c:170444:24 in sqlite3.h
// sqlite3_rollback_hook at sqlite3.c:170088:18 in sqlite3.h
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

static int auth_callback(void*, int, const char*, const char*, const char*, const char*) {
    return SQLITE_OK;
}

static void profile_callback(void*, const char*, sqlite3_uint64) {}

static void rollback_callback(void*) {}

extern "C" int LLVMFuzzerTestOneInput_150(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    int action = Data[0] % 5;
    switch (action) {
        case 0:
            sqlite3_set_authorizer(db, auth_callback, nullptr);
            break;
        case 1:
            sqlite3_profile(db, profile_callback, nullptr);
            break;
        case 2:
            sqlite3_total_changes64(db);
            break;
        case 3:
            sqlite3_errmsg16(db);
            break;
        case 4:
            sqlite3_rollback_hook(db, rollback_callback, nullptr);
            break;
        default:
            break;
    }

    sqlite3_close(db);
    return 0;
}