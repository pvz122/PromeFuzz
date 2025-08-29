// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:129822:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_stmt_explain at sqlite3.c:79385:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:77530:16 in sqlite3.h
// sqlite3_stmt_status at sqlite3.c:79453:16 in sqlite3.h
// sqlite3_expired at sqlite3.c:77410:16 in sqlite3.h
// sqlite3_transfer_bindings at sqlite3.c:79338:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:77480:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt1 = nullptr, *stmt2 = nullptr;
    const char *sql = "SELECT * FROM dummy_table";

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt1, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }
    if (sqlite3_prepare_v2(db, sql, -1, &stmt2, nullptr) != SQLITE_OK) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0;
    }

    int mode = Data[0] % 3;
    sqlite3_stmt_explain(stmt1, mode);

    sqlite3_clear_bindings(stmt1);

    int op = Data[0] % 10;
    int resetFlg = Data[0] % 2;
    sqlite3_stmt_status(stmt1, op, resetFlg);

    sqlite3_expired(stmt1);

    sqlite3_transfer_bindings(stmt1, stmt2);

    sqlite3_finalize(stmt2);
    sqlite3_finalize(stmt1);
    sqlite3_close(db);
    return 0;
}