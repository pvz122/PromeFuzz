// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:77509:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:79096:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:77509:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_value_encoding at sqlite3.c:77710:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_column_text at sqlite3.c:78779:33 in sqlite3.h
// sqlite3_column_text at sqlite3.c:78779:33 in sqlite3.h
// sqlite3_bind_value at sqlite3.c:79207:16 in sqlite3.h
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
#include <stdint.h>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE t1(a); INSERT INTO t1 VALUES(?);";

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_step(stmt); // Execute CREATE TABLE
    sqlite3_reset(stmt);

    sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_STATIC);
    sqlite3_step(stmt); // Execute INSERT

    sqlite3_reset(stmt);
    sqlite3_step(stmt); // Execute SELECT

    sqlite3_value *value1 = sqlite3_column_value(stmt, 0);
    int encoding1 = sqlite3_value_encoding(value1);

    sqlite3_value *value2 = sqlite3_column_value(stmt, 0);
    const unsigned char *text1 = sqlite3_column_text(stmt, 0);
    const unsigned char *text2 = sqlite3_column_text(stmt, 0);

    sqlite3_bind_value(stmt, 1, value1);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}