// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_complete16 at sqlite3.c:167594:16 in sqlite3.h
// sqlite3_open16 at sqlite3.c:171369:16 in sqlite3.h
// sqlite3_prepare16_v3 at sqlite3.c:129962:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare16_v2 at sqlite3.c:129950:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare16 at sqlite3.c:129938:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Convert input to UTF-16
    size_t utf16_size = Size / 2;
    uint16_t *utf16_data = new uint16_t[utf16_size + 1]; // +1 to ensure null-termination
    for (size_t i = 0; i < utf16_size; ++i) {
        utf16_data[i] = (Data[i * 2] << 8) | Data[i * 2 + 1];
    }
    utf16_data[utf16_size] = 0; // Null-terminate the UTF-16 string

    // Test sqlite3_complete16
    sqlite3_complete16(utf16_data);

    // Test sqlite3_open16
    sqlite3 *db = nullptr;
    if (sqlite3_open16(utf16_data, &db) == SQLITE_OK) {
        // Test sqlite3_prepare16_v3, sqlite3_prepare16_v2, and sqlite3_prepare16
        sqlite3_stmt *stmt = nullptr;
        const void *pzTail = nullptr;
        sqlite3_prepare16_v3(db, utf16_data, utf16_size * 2, 0, &stmt, &pzTail);
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        sqlite3_prepare16_v2(db, utf16_data, utf16_size * 2, &stmt, &pzTail);
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        sqlite3_prepare16(db, utf16_data, utf16_size * 2, &stmt, &pzTail);
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }

    delete[] utf16_data;
    return 0;
}