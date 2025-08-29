// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_memory_highwater at sqlite3.c:17097:26 in sqlite3.h
// sqlite3_memory_used at sqlite3.c:17086:26 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_close(db);
    sqlite3_int64 highwater = sqlite3_memory_highwater(0);
    sqlite3_int64 used = sqlite3_memory_used();

    return 0;
}