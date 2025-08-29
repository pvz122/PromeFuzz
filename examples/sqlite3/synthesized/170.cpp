// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_sourceid at sqlite3.c:247679:24 in sqlite3.h
// sqlite3_libversion_number at sqlite3.c:167826:16 in sqlite3.h
// sqlite3_libversion at sqlite3.c:167813:24 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:79172:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:79129:16 in sqlite3.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_170(const uint8_t *Data, size_t Size) {
    // Test sqlite3_sourceid
    const char *sourceid = sqlite3_sourceid();
    (void)sourceid;

    // Test sqlite3_libversion_number
    int version_number = sqlite3_libversion_number();
    (void)version_number;

    // Test sqlite3_libversion
    const char *libversion = sqlite3_libversion();
    (void)libversion;

    // Test sqlite3_bind_text and sqlite3_bind_int
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
        const char *sql = "CREATE TABLE test (id INTEGER, name TEXT);";
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            // Bind text
            const char *text_data = reinterpret_cast<const char *>(Data);
            int text_length = Size > 0 ? Size : 0;
            sqlite3_bind_text(stmt, 1, text_data, text_length, SQLITE_STATIC);

            // Bind int
            int int_data = Size > 0 ? static_cast<int>(Data[0]) : 0;
            sqlite3_bind_int(stmt, 2, int_data);

            sqlite3_finalize(stmt);
        }
        sqlite3_close(db);
    }

    return 0;
}