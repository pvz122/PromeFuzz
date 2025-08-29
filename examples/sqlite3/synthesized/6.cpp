// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_hard_heap_limit64 at sqlite3.c:17026:26 in sqlite3.h
// sqlite3_limit at sqlite3.c:170661:16 in sqlite3.h
// sqlite3_db_config at sqlite3.c:168665:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
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

static int auth_callback(void*, int, const char*, const char*, const char*, const char*) {
    return SQLITE_OK;
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_int64) + sizeof(int) * 3) {
        return 0;
    }

    sqlite3_int64 heap_limit = *reinterpret_cast<const sqlite3_int64*>(Data);
    int limit_id = *reinterpret_cast<const int*>(Data + sizeof(sqlite3_int64));
    int limit_val = *reinterpret_cast<const int*>(Data + sizeof(sqlite3_int64) + sizeof(int));
    int db_config_op = *reinterpret_cast<const int*>(Data + sizeof(sqlite3_int64) + sizeof(int) * 2);

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_hard_heap_limit64(heap_limit);
    sqlite3_limit(db, limit_id, limit_val);
    sqlite3_db_config(db, db_config_op, 0);
    sqlite3_set_authorizer(db, auth_callback, nullptr);

    sqlite3_close(db);
    return 0;
}