// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_error_toobig at sqlite3.c:78064:17 in sqlite3.h
// sqlite3_result_error_nomem at sqlite3.c:78075:17 in sqlite3.h
// sqlite3_result_null at sqlite3.c:77891:17 in sqlite3.h
// sqlite3_result_int64 at sqlite3.c:77884:17 in sqlite3.h
// sqlite3_result_double at sqlite3.c:77852:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3_context *context = nullptr;

    switch (Data[0] % 5) {
        case 0:
            sqlite3_result_error_toobig(context);
            break;
        case 1:
            sqlite3_result_error_nomem(context);
            break;
        case 2:
            sqlite3_result_null(context);
            break;
        case 3:
            sqlite3_result_int64(context, static_cast<sqlite3_int64>(Size));
            break;
        case 4:
            sqlite3_result_double(context, static_cast<double>(Size));
            break;
        default:
            break;
    }

    return 0;
}