// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvaprintf at mprintf.c:1132:7 in mprintf.h
// curl_mvsnprintf at mprintf.c:1070:5 in mprintf.h
// curl_mvprintf at mprintf.c:1215:5 in mprintf.h
// curl_mvfprintf at mprintf.c:1220:5 in mprintf.h
// curl_maprintf at mprintf.c:1150:7 in mprintf.h
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
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>

static void test_curl_mvaprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *result_mvaprintf = curl_mvaprintf(format, args);
    va_end(args);
    if (result_mvaprintf) free(result_mvaprintf);
}

static void test_curl_mvsnprintf(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    int result_mvsnprintf = curl_mvsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
}

static void test_curl_mvprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result_mvprintf = curl_mvprintf(format, args);
    va_end(args);
}

static void test_curl_mvfprintf(const char *format, ...) {
    FILE *dummy_file = fopen("./dummy_file", "w");
    if (dummy_file) {
        va_list args;
        va_start(args, format);
        int result_mvfprintf = curl_mvfprintf(dummy_file, format, args);
        va_end(args);
        fclose(dummy_file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare format string and arguments
    const char *format = reinterpret_cast<const char*>(Data);
    size_t format_len = strnlen(format, Size);
    if (format_len == Size) return 0;

    const char *args_str = reinterpret_cast<const char*>(Data + format_len + 1);
    size_t args_len = Size - (format_len + 1);

    // Test curl_maprintf
    char *result_maprintf = curl_maprintf(format, args_str);
    if (result_maprintf) free(result_maprintf);

    // Test curl_mvaprintf
    test_curl_mvaprintf(format, args_str);

    // Test curl_mvsnprintf
    test_curl_mvsnprintf(format, args_str);

    // Test curl_mvprintf
    test_curl_mvprintf(format, args_str);

    // Test curl_mvfprintf
    test_curl_mvfprintf(format, args_str);

    return 0;
}