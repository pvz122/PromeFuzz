// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_errcode at sqlite3.c:170486:16 in sqlite3.h
// sqlite3_total_changes at sqlite3.c:168873:16 in sqlite3.h
// sqlite3_get_autocommit at sqlite3.c:171593:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:77509:16 in sqlite3.h
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

static int authorizer_callback(void* pUserData, int action_code, const char* arg1, const char* arg2, const char* arg3, const char* arg4) {
    return SQLITE_OK;
}

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Fuzz sqlite3_set_authorizer
    sqlite3_set_authorizer(db, authorizer_callback, nullptr);

    // Fuzz sqlite3_errcode
    int errcode = sqlite3_errcode(db);

    // Fuzz sqlite3_total_changes
    int total_changes = sqlite3_total_changes(db);

    // Fuzz sqlite3_get_autocommit
    int autocommit = sqlite3_get_autocommit(db);

    // Fuzz sqlite3_reset
    sqlite3_stmt *stmt;
    const char *sql = "SELECT 1";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_reset(stmt);
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}