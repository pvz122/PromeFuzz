// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:170429:16 in sqlite3.h
// sqlite3_total_changes64 at sqlite3.c:168864:26 in sqlite3.h
// sqlite3_extended_result_codes at sqlite3.c:171797:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:168857:16 in sqlite3.h
// sqlite3_close_v2 at sqlite3.c:169059:16 in sqlite3.h
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
#include <stdint.h>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    // Fuzz sqlite3_error_offset
    int offset = sqlite3_error_offset(db);

    // Fuzz sqlite3_total_changes64
    sqlite3_int64 total_changes = sqlite3_total_changes64(db);

    // Fuzz sqlite3_extended_result_codes
    int onoff = Data[0] % 2;
    sqlite3_extended_result_codes(db, onoff);

    // Fuzz sqlite3_changes
    int changes = sqlite3_changes(db);

    // Fuzz sqlite3_close_v2
    sqlite3_close_v2(db);

    return 0;
}