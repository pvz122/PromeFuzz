// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvsprintf at mprintf.c:1208:5 in mprintf.h
// curl_mvfprintf at mprintf.c:1220:5 in mprintf.h
// curl_mvsnprintf at mprintf.c:1070:5 in mprintf.h
// curl_mvprintf at mprintf.c:1215:5 in mprintf.h
// curl_mprintf at mprintf.c:1187:5 in mprintf.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/mprintf.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void test_curl_mvsprintf(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    curl_mvsprintf(buffer, format, args);
    va_end(args);
}

static void test_curl_mvfprintf(FILE *fd, const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvfprintf(fd, format, args);
    va_end(args);
}

static void test_curl_mvsnprintf(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    curl_mvsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
}

static void test_curl_mvprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvprintf(format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *fd = fopen("./dummy_file", "wb");
    if (!fd) return 0;

    // Prepare format string and arguments
    const char *format = reinterpret_cast<const char*>(Data);
    size_t format_len = strnlen(format, Size);
    if (format_len >= Size) return 0;

    const char *args_str = reinterpret_cast<const char*>(Data + format_len + 1);
    size_t args_len = Size - (format_len + 1);

    // Test curl_mvsprintf
    test_curl_mvsprintf(format, args_str);

    // Test curl_mvfprintf
    test_curl_mvfprintf(fd, format, args_str);

    // Test curl_mvsnprintf
    test_curl_mvsnprintf(format, args_str);

    // Test curl_mvprintf
    test_curl_mvprintf(format, args_str);

    // Test curl_mprintf
    curl_mprintf(format, args_str);

    fclose(fd);
    return 0;
}