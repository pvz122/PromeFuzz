// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_step at sqlite3.c:78276:16 in sqlite3.h
// sqlite3_data_count at sqlite3.c:78639:16 in sqlite3.h
// sqlite3_stmt_status at sqlite3.c:79453:16 in sqlite3.h
// sqlite3_stmt_busy at sqlite3.c:79421:16 in sqlite3.h
// sqlite3_stmt_readonly at sqlite3.c:79370:16 in sqlite3.h
// sqlite3_expired at sqlite3.c:77410:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_147(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    const char *sql = "CREATE TABLE t1 (a, b);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    sql = "SELECT * FROM t1;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    sqlite3_step(stmt);
    sqlite3_data_count(stmt);

    sqlite3_stmt_status(stmt, SQLITE_STMTSTATUS_FULLSCAN_STEP, 1);

    sqlite3_stmt_busy(stmt);

    sqlite3_stmt_readonly(stmt);

    sqlite3_expired(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}