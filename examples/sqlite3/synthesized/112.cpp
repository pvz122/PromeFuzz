// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_keyword_count at sqlite3.c:166570:16 in sqlite3.h
// sqlite3_keyword_name at sqlite3.c:166563:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare16 at sqlite3.c:129938:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_keyword_check at sqlite3.c:166571:16 in sqlite3.h
// sqlite3_keyword_count at sqlite3.c:166570:16 in sqlite3.h
// sqlite3_test_control at sqlite3.c:171863:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz sqlite3_keyword_name
    int keyword_index = Data[0] % sqlite3_keyword_count();
    const char *keyword_name;
    int keyword_length;
    sqlite3_keyword_name(keyword_index, &keyword_name, &keyword_length);

    // Fuzz sqlite3_prepare16
    sqlite3 *db;
    sqlite3_open(":memory:", &db);
    sqlite3_stmt *stmt;
    const void *tail;
    if (Size >= 4) {  // Ensure there's enough data for UTF-16 encoding
        // Ensure the input is properly aligned for UTF-16
        const void *utf16_data = Data;
        size_t utf16_size = Size - (Size % 2); // Ensure even number of bytes
        sqlite3_prepare16(db, utf16_data, utf16_size, &stmt, &tail);
        if (stmt) {
            sqlite3_finalize(stmt);
        }
    }
    sqlite3_close(db);

    // Fuzz sqlite3_keyword_check
    char *keyword = (char *)malloc(Size + 1);
    if (keyword) {
        memcpy(keyword, Data, Size);
        keyword[Size] = '\0';
        sqlite3_keyword_check(keyword, Size);
        free(keyword);
    }

    // Fuzz sqlite3_keyword_count
    sqlite3_keyword_count();

    // Fuzz sqlite3_test_control
    sqlite3_test_control(SQLITE_TESTCTRL_PRNG_SAVE, 0);

    return 0;
}