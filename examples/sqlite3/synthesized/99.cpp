// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_changes64 at sqlite3.c:168848:26 in sqlite3.h
// sqlite3_set_last_insert_rowid at sqlite3.c:168833:17 in sqlite3.h
// sqlite3_total_changes64 at sqlite3.c:168864:26 in sqlite3.h
// sqlite3_interrupt at sqlite3.c:169598:17 in sqlite3.h
// sqlite3_last_insert_rowid at sqlite3.c:168820:25 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Use the first byte to determine which function to test
    uint8_t function_selector = Data[0] % 5;

    switch (function_selector) {
        case 0: {
            sqlite3_changes64(db);
            break;
        }
        case 1: {
            sqlite3_int64 rowid = static_cast<sqlite3_int64>(Size);
            sqlite3_set_last_insert_rowid(db, rowid);
            break;
        }
        case 2: {
            sqlite3_total_changes64(db);
            break;
        }
        case 3: {
            sqlite3_interrupt(db);
            break;
        }
        case 4: {
            sqlite3_last_insert_rowid(db);
            break;
        }
        default: {
            break;
        }
    }

    sqlite3_close(db);
    return 0;
}