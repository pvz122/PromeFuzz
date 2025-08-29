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
// sqlite3_bind_zeroblob at sqlite3.c:79241:16 in sqlite3.h
// sqlite3_bind_zeroblob64 at sqlite3.c:79256:16 in sqlite3.h
// sqlite3_bind_blob64 at sqlite3.c:79108:16 in sqlite3.h
// sqlite3_bind_text16 at sqlite3.c:79197:16 in sqlite3.h
// sqlite3_bind_null at sqlite3.c:79143:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
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

    sql = "INSERT INTO test (data) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    int param_index = 1;
    int n = static_cast<int>(Data[0]);
    sqlite3_bind_zeroblob(stmt, param_index, n);

    sqlite3_uint64 n64 = static_cast<sqlite3_uint64>(Data[0]);
    sqlite3_bind_zeroblob64(stmt, param_index, n64);

    const void *blob_data = Data;
    sqlite3_uint64 blob_size = Size;
    sqlite3_bind_blob64(stmt, param_index, blob_data, blob_size, SQLITE_TRANSIENT);

    const void *text16_data = Data;
    int text16_size = static_cast<int>(Size);
    sqlite3_bind_text16(stmt, param_index, text16_data, text16_size, SQLITE_TRANSIENT);

    sqlite3_bind_null(stmt, param_index);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}