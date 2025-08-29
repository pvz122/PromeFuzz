// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_errcode at sqlite3.c:170486:16 in sqlite3.h
// sqlite3_is_interrupted at sqlite3.c:169614:16 in sqlite3.h
// sqlite3_extended_errcode at sqlite3.c:170495:16 in sqlite3.h
// sqlite3_close_v2 at sqlite3.c:169059:16 in sqlite3.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_116(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = nullptr;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Fuzz sqlite3_errmsg
    const char *errmsg = sqlite3_errmsg(db);
    if (errmsg) {
        // Do nothing, just ensure the function is called
    }

    // Fuzz sqlite3_errcode
    int errcode = sqlite3_errcode(db);
    if (errcode) {
        // Do nothing, just ensure the function is called
    }

    // Fuzz sqlite3_is_interrupted
    int interrupted = sqlite3_is_interrupted(db);
    if (interrupted) {
        // Do nothing, just ensure the function is called
    }

    // Fuzz sqlite3_extended_errcode
    int extended_errcode = sqlite3_extended_errcode(db);
    if (extended_errcode) {
        // Do nothing, just ensure the function is called
    }

    // Fuzz sqlite3_close_v2
    rc = sqlite3_close_v2(db);
    if (rc != SQLITE_OK) {
        // Handle error if needed
    }

    return 0;
}