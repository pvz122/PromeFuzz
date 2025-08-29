// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_blob_read at sqlite3.c:89944:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:170403:24 in sqlite3.h
// sqlite3_create_function at sqlite3.c:169818:16 in sqlite3.h
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

static void dummy_func(sqlite3_context*, int, sqlite3_value**) {}

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    const char *err_msg1 = sqlite3_errmsg(db);

    sqlite3_blob *blob = nullptr;
    char buffer[1024];
    int blob_read_result = sqlite3_blob_read(blob, buffer, sizeof(buffer), 0);

    const char *err_msg2 = sqlite3_errmsg(db);

    int create_func_result = sqlite3_create_function(db, "dummy_func", 1, SQLITE_UTF8, nullptr, dummy_func, nullptr, nullptr);

    sqlite3_close(db);
    return 0;
}