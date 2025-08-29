// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_extended_errcode at sqlite3.c:170495:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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
#include <cstdio>
#include <cstring>
#include <cstdarg>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    char *zSql = sqlite3_mprintf("%.*s", (int)Size, Data);
    if (!zSql) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_stmt *stmt;
    const char *pzTail;
    int rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);

    int errcode = sqlite3_extended_errcode(db);
    const char *errmsg = sqlite3_errmsg(db);

    sqlite3_free(zSql);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}