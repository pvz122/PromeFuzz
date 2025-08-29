// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_get_clientdata at sqlite3.c:171517:18 in sqlite3.h
// sqlite3_trace_v2 at sqlite3.c:169978:16 in sqlite3.h
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_backup_init at sqlite3.c:69129:28 in sqlite3.h
// sqlite3_backup_finish at sqlite3.c:69560:16 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) return 0;

    // Fuzz sqlite3_errmsg
    const char *errmsg = sqlite3_errmsg(db);

    // Fuzz sqlite3_set_authorizer
    rc = sqlite3_set_authorizer(db, [](void*, int, const char*, const char*, const char*, const char*) {
        return SQLITE_OK;
    }, nullptr);

    // Fuzz sqlite3_get_clientdata
    const char *name = reinterpret_cast<const char*>(Data);
    void *clientdata = sqlite3_get_clientdata(db, name);

    // Fuzz sqlite3_trace_v2
    rc = sqlite3_trace_v2(db, SQLITE_TRACE_STMT, [](unsigned, void*, void*, void*) {
        return 0;
    }, nullptr);

    // Fuzz sqlite3_backup_init
    sqlite3 *db2;
    rc = sqlite3_open(":memory:", &db2);
    if (rc == SQLITE_OK) {
        sqlite3_backup *backup = sqlite3_backup_init(db2, "main", db, "main");
        if (backup) {
            sqlite3_backup_finish(backup);
        }
        sqlite3_close(db2);
    }

    sqlite3_close(db);
    return 0;
}