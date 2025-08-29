// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:79096:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_column_bytes16 at sqlite3.c:78759:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
// sqlite3_column_bytes16 at sqlite3.c:78759:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
// sqlite3_column_value at sqlite3.c:78784:27 in sqlite3.h
// sqlite3_value_encoding at sqlite3.c:77710:16 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:78754:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:78744:24 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (col1 BLOB);";
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);

    sql = "INSERT INTO test (col1) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);

    sql = "SELECT col1 FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_column_bytes16(stmt, 0);
    sqlite3_column_blob(stmt, 0);
    sqlite3_column_bytes16(stmt, 0);
    sqlite3_column_blob(stmt, 0);

    sqlite3_value *value = sqlite3_column_value(stmt, 0);
    sqlite3_value_encoding(value);

    sqlite3_column_bytes(stmt, 0);
    sqlite3_column_blob(stmt, 0);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}