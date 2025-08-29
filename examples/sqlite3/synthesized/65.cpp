// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_progress_handler at sqlite3.c:169515:17 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_errcode at sqlite3.c:170486:16 in sqlite3.h
// sqlite3_set_authorizer at sqlite3.c:108676:16 in sqlite3.h
// sqlite3_commit_hook at sqlite3.c:170038:18 in sqlite3.h
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

static int progress_callback(void *data) {
    return 0;
}

static int authorizer_callback(void *userData, int actionCode, const char *arg1, const char *arg2, const char *arg3, const char *arg4) {
    return SQLITE_OK;
}

static int commit_hook_callback(void *data) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    int nOps = Data[0];
    sqlite3_progress_handler(db, nOps, progress_callback, nullptr);

    const char *errmsg = sqlite3_errmsg(db);
    int errcode = sqlite3_errcode(db);

    sqlite3_set_authorizer(db, authorizer_callback, nullptr);

    sqlite3_commit_hook(db, commit_hook_callback, nullptr);

    sqlite3_close(db);
    return 0;
}