// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mfprintf at mprintf.c:1198:5 in mprintf.h
// curl_mvsprintf at mprintf.c:1208:5 in mprintf.h
// curl_mvfprintf at mprintf.c:1220:5 in mprintf.h
// curl_mvsnprintf at mprintf.c:1070:5 in mprintf.h
// curl_mvprintf at mprintf.c:1215:5 in mprintf.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include "mprintf.h"

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *dummy_file = fopen("./dummy_file", "w");
    if (!dummy_file) return 0;

    char format[256];
    char buffer[256];
    size_t format_len = Size > sizeof(format) ? sizeof(format) - 1 : Size;
    memcpy(format, Data, format_len);
    format[format_len] = '\0';

    // Use a variadic function to handle va_start properly
    auto call_mprintf_functions = [&](const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        curl_mfprintf(dummy_file, fmt, "test");
        curl_mvsprintf(buffer, fmt, args);
        curl_mvfprintf(dummy_file, fmt, args);
        curl_mvsnprintf(buffer, sizeof(buffer), fmt, args);
        curl_mvprintf(fmt, args);
        va_end(args);
    };

    call_mprintf_functions(format);

    fclose(dummy_file);
    return 0;
}