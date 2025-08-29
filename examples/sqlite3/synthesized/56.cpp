// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_create_function_v2 at sqlite3.c:169831:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:169818:16 in sqlite3.h
// sqlite3_create_window_function at sqlite3.c:169845:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_column_text at sqlite3.c:78779:33 in sqlite3.h
// sqlite3_result_text at sqlite3.c:77939:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_create_function16 at sqlite3.c:169862:16 in sqlite3.h
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

static void dummy_func(sqlite3_context*, int, sqlite3_value**) {}
static void dummy_step(sqlite3_context*, int, sqlite3_value**) {}
static void dummy_final(sqlite3_context*) {}
static void dummy_destroy(void*) {}

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return 0;

    char funcName[256];
    size_t len = Size < 255 ? Size : 255;
    memcpy(funcName, Data, len);
    funcName[len] = '\0';

    int nArg = static_cast<int>(Data[0]);
    int eTextRep = SQLITE_UTF8;
    void *pApp = nullptr;

    sqlite3_create_function_v2(db, funcName, nArg, eTextRep, pApp, dummy_func, dummy_step, dummy_final, dummy_destroy);
    sqlite3_create_function(db, funcName, nArg, eTextRep, pApp, dummy_func, dummy_step, dummy_final);
    sqlite3_create_window_function(db, funcName, nArg, eTextRep, pApp, dummy_step, dummy_final, nullptr, nullptr, dummy_destroy);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT 'dummy_text'";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *resultText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            sqlite3_context *ctx = nullptr;
            sqlite3_result_text(ctx, resultText, -1, SQLITE_TRANSIENT);
        }
        sqlite3_finalize(stmt);
    }

    sqlite3_create_function16(db, reinterpret_cast<const void*>(funcName), nArg, eTextRep, pApp, dummy_func, dummy_step, dummy_final);

    sqlite3_close(db);
    return 0;
}