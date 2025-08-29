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

static void test_curl_mvfprintf(const char *format, ...) {
    FILE *file = fopen("./dummy_file", "w");
    if (!file) return;
    va_list args;
    va_start(args, format);
    curl_mvfprintf(file, format, args);
    va_end(args);
    fclose(file);
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

static void test_curl_mprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mprintf(format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) return 0;
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    test_curl_mvsprintf("%s", buffer);
    test_curl_mvfprintf("%s", buffer);
    test_curl_mvsnprintf("%s", buffer);
    test_curl_mvprintf("%s", buffer);
    test_curl_mprintf("%s", buffer);

    free(buffer);
    return 0;
}