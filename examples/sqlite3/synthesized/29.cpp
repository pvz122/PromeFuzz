// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:171349:16 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
// sqlite3_close at sqlite3.c:169058:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    int rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) return 0;

    sqlite3_str *str1 = sqlite3_str_new(db);
    sqlite3_str *str2 = sqlite3_str_new(db);

    char *result1 = sqlite3_str_finish(str1);
    char *result2 = sqlite3_str_finish(str2);

    sqlite3_close(db);

    sqlite3_free(result1);
    sqlite3_free(result2);

    return 0;
}