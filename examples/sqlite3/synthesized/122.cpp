// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:79172:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:77726:27 in sqlite3.h
// sqlite3_value_bytes16 at sqlite3.c:77579:16 in sqlite3.h
// sqlite3_value_numeric_type at sqlite3.c:80698:16 in sqlite3.h
// sqlite3_value_encoding at sqlite3.c:77710:16 in sqlite3.h
// sqlite3_value_nochange at sqlite3.c:77715:16 in sqlite3.h
// sqlite3_value_type at sqlite3.c:77626:16 in sqlite3.h
// sqlite3_value_free at sqlite3.c:77752:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    const char *sql = "SELECT ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, reinterpret_cast<const char*>(Data), Size, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_value *value = sqlite3_column_value(stmt, 0);
        sqlite3_value *protected_value = sqlite3_value_dup(value);
        if (protected_value) {
            sqlite3_value_bytes16(protected_value);
            sqlite3_value_numeric_type(protected_value);
            sqlite3_value_encoding(protected_value);
            sqlite3_value_nochange(protected_value);
            sqlite3_value_type(protected_value);
            sqlite3_value_free(protected_value);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}