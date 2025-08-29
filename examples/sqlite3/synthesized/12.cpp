// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open_v2 at sqlite3.c:171356:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_open_v2 at sqlite3.c:171356:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_deserialize at sqlite3.c:40596:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_create_function at sqlite3.c:169818:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    const char *zVfs = nullptr;

    // First call to sqlite3_open_v2
    int rc = sqlite3_open_v2("./dummy_file", &db, flags, zVfs);
    if (rc != SQLITE_OK) {
        const char *errMsg = sqlite3_errmsg(db);
        sqlite3_close(db);
        return 0;
    }

    // Second call to sqlite3_open_v2
    rc = sqlite3_open_v2("./dummy_file", &db, flags, zVfs);
    if (rc != SQLITE_OK) {
        const char *errMsg = sqlite3_errmsg(db);
        sqlite3_close(db);
        return 0;
    }

    // Call to sqlite3_deserialize
    unsigned char *pData = (unsigned char *)Data;
    sqlite3_int64 szDb = Size;
    sqlite3_int64 szBuf = Size;
    unsigned mFlags = 0;
    rc = sqlite3_deserialize(db, "main", pData, szDb, szBuf, mFlags);
    if (rc != SQLITE_OK) {
        const char *errMsg = sqlite3_errmsg(db);
        sqlite3_close(db);
        return 0;
    }

    // Call to sqlite3_create_function
    const char *zFunctionName = "test_func";
    int nArg = 1;
    int eTextRep = SQLITE_UTF8;
    void *pApp = nullptr;
    rc = sqlite3_create_function(db, zFunctionName, nArg, eTextRep, pApp, nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK) {
        const char *errMsg = sqlite3_errmsg(db);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_close(db);
    return 0;
}