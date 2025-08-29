// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_create_collation at sqlite3.c:171408:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_extended_result_codes at sqlite3.c:171797:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_collation_needed at sqlite3.c:171476:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_int64 at sqlite3.c:78774:25 in sqlite3.h
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

static int auth_callback(void* pUserData, int action_code, const char* arg1, const char* arg2, const char* arg3, const char* arg4) {
    return SQLITE_OK;
}

static void collation_callback(void* pUserData, sqlite3* db, int eTextRep, const char* collation_name) {
    sqlite3_create_collation(db, collation_name, eTextRep, nullptr, nullptr);
}

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3* db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    int onoff = Data[0] % 2;
    sqlite3_extended_result_codes(db, onoff);

    sqlite3_set_authorizer(db, auth_callback, nullptr);

    sqlite3_collation_needed(db, nullptr, collation_callback);

    const char* sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    sql = "INSERT INTO test (value) VALUES ('fuzz');";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    sql = "SELECT id, value FROM test;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            sqlite3_column_int64(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}