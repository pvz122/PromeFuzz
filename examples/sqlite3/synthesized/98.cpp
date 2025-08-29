// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_int at sqlite3.c:77877:17 in sqlite3.h
// sqlite3_result_int64 at sqlite3.c:77884:17 in sqlite3.h
// sqlite3_result_null at sqlite3.c:77891:17 in sqlite3.h
// sqlite3_vtab_nochange at sqlite3.c:78371:16 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    sqlite3_context* context = nullptr;
    int intValue = 0;
    sqlite3_int64 int64Value = 0;

    if (Size >= sizeof(int)) {
        intValue = *reinterpret_cast<const int*>(Data);
    }
    if (Size >= sizeof(sqlite3_int64)) {
        int64Value = *reinterpret_cast<const sqlite3_int64*>(Data);
    }

    sqlite3_result_int(context, intValue);
    sqlite3_result_int64(context, int64Value);
    sqlite3_result_null(context);
    sqlite3_vtab_nochange(context);

    return 0;
}