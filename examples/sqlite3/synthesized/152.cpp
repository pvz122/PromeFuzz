// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_error_code at sqlite3.c:78049:17 in sqlite3.h
// sqlite3_result_int at sqlite3.c:77877:17 in sqlite3.h
// sqlite3_result_error16 at sqlite3.c:77868:17 in sqlite3.h
// sqlite3_result_zeroblob64 at sqlite3.c:78030:16 in sqlite3.h
// sqlite3_result_zeroblob at sqlite3.c:78027:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    sqlite3_context* ctx = nullptr;
    sqlite3_value* value = nullptr;

    int error_code = *reinterpret_cast<const int*>(Data);
    sqlite3_result_error_code(ctx, error_code);

    int int_value = *reinterpret_cast<const int*>(Data);
    sqlite3_result_int(ctx, int_value);

    const void* error_msg = reinterpret_cast<const void*>(Data);
    sqlite3_result_error16(ctx, error_msg, Size);

    if (Size >= sizeof(sqlite3_uint64)) {
        sqlite3_uint64 blob_size = *reinterpret_cast<const sqlite3_uint64*>(Data);
        sqlite3_result_zeroblob64(ctx, blob_size);
    }

    int blob_size_int = *reinterpret_cast<const int*>(Data);
    sqlite3_result_zeroblob(ctx, blob_size_int);

    return 0;
}