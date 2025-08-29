// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:124106:16 in sqlite3.h
// sqlite3_changes64 at sqlite3.c:168848:26 in sqlite3.h
// sqlite3_wal_hook at sqlite3.c:170218:18 in sqlite3.h
// sqlite3_interrupt at sqlite3.c:169598:17 in sqlite3.h
// sqlite3_total_changes at sqlite3.c:168873:16 in sqlite3.h
// sqlite3_rollback_hook at sqlite3.c:170088:18 in sqlite3.h
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

static int wal_callback(void *pArg, sqlite3 *db, const char *zDb, int nPages) {
    return SQLITE_OK;
}

static void rollback_callback(void *pArg) {
    // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Execute a simple SQL statement to trigger changes
    const char *sql = "CREATE TABLE t1(a, b);";
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

    // Fuzz sqlite3_changes64
    sqlite3_changes64(db);

    // Fuzz sqlite3_wal_hook
    sqlite3_wal_hook(db, wal_callback, nullptr);

    // Fuzz sqlite3_interrupt
    sqlite3_interrupt(db);

    // Fuzz sqlite3_total_changes
    sqlite3_total_changes(db);

    // Fuzz sqlite3_rollback_hook
    sqlite3_rollback_hook(db, rollback_callback, nullptr);

    sqlite3_close(db);
    return 0;
}