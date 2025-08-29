// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_error_code at sqlite3.c:78049:17 in sqlite3.h
// sqlite3_result_int at sqlite3.c:77877:17 in sqlite3.h
// sqlite3_result_error at sqlite3.c:77859:17 in sqlite3.h
// sqlite3_result_error16 at sqlite3.c:77868:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    sqlite3_context* ctx = nullptr;
    int error_code = *reinterpret_cast<const int*>(Data);
    const char* error_msg = reinterpret_cast<const char*>(Data + sizeof(int));
    size_t error_msg_len = Size - sizeof(int);

    sqlite3_result_error_code(ctx, error_code);
    sqlite3_result_int(ctx, error_code);
    sqlite3_result_error(ctx, error_msg, error_msg_len);
    sqlite3_result_error16(ctx, error_msg, error_msg_len);
    sqlite3_result_zeroblob(ctx, error_code);

    return 0;
}