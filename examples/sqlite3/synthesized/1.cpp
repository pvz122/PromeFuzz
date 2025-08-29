// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_text at sqlite3.c:78779:33 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *tail;
    const char *sql = reinterpret_cast<const char*>(Data);
    int sql_len = Size;

    if (sqlite3_prepare_v2(db, sql, sql_len, &stmt, &tail) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *text = sqlite3_column_text(stmt, 0);
        if (text) {
            char *formatted = sqlite3_mprintf("Text: %s", text);
            if (formatted) {
                sqlite3_str *str = sqlite3_str_new(db);
                sqlite3_str_appendf(str, "%s", formatted);
                sqlite3_str_appendf(str, " (appended)");
                sqlite3_free(formatted);
                sqlite3_str_finish(str);
            }
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}