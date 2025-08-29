// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_errcode at sqlite3.c:170486:16 in sqlite3.h
// sqlite3_extended_errcode at sqlite3.c:170495:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:170429:16 in sqlite3.h
// sqlite3_system_errno at sqlite3.c:170504:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = nullptr;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Use the first byte to determine which function to test
    uint8_t function_selector = Data[0] % 5;

    switch (function_selector) {
        case 0:
            sqlite3_errmsg(db);
            break;
        case 1:
            sqlite3_errcode(db);
            break;
        case 2:
            sqlite3_extended_errcode(db);
            break;
        case 3:
            sqlite3_error_offset(db);
            break;
        case 4:
            sqlite3_system_errno(db);
            break;
        default:
            break;
    }

    sqlite3_close(db);
    return 0;
}