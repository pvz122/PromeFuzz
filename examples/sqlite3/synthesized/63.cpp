// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_str_appendchar at sqlite3.c:18856:17 in sqlite3.h
// sqlite3_str_append at sqlite3.c:18884:17 in sqlite3.h
// sqlite3_str_length at sqlite3.c:18979:16 in sqlite3.h
// sqlite3_str_errcode at sqlite3.c:18974:16 in sqlite3.h
// sqlite3_str_value at sqlite3.c:18984:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    sqlite3_str *str = sqlite3_str_new(nullptr);
    if (!str) return 0;

    // Append a character N times
    int N = Data[0] % 256;
    char C = Data[1] % 256;
    sqlite3_str_appendchar(str, N, C);

    // Append a string
    const char *zIn = reinterpret_cast<const char*>(Data);
    int appendSize = Size < 1024 ? Size : 1024;
    sqlite3_str_append(str, zIn, appendSize);

    // Get the length of the string
    int length = sqlite3_str_length(str);

    // Get the error code
    int errcode = sqlite3_str_errcode(str);

    // Get the string value
    char *value = sqlite3_str_value(str);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}