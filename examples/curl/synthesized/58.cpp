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
#include <mprintf.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>

static void test_curl_mvsprintf(const char *format, const char *data, ...) {
    char output_buffer[1024];
    va_list args;
    va_start(args, data);
    curl_mvsprintf(output_buffer, format, args);
    va_end(args);
}

static void test_curl_mvfprintf(FILE *fd, const char *format, const char *data, ...) {
    va_list args;
    va_start(args, data);
    curl_mvfprintf(fd, format, args);
    va_end(args);
}

static void test_curl_mvsnprintf(const char *format, const char *data, ...) {
    char output_buffer[1024];
    va_list args;
    va_start(args, data);
    curl_mvsnprintf(output_buffer, sizeof(output_buffer), format, args);
    va_end(args);
}

static void test_curl_mvprintf(const char *format, const char *data, ...) {
    va_list args;
    va_start(args, data);
    curl_mvprintf(format, args);
    va_end(args);
}

static void test_curl_mprintf(const char *format, const char *data) {
    curl_mprintf(format, data);
}

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) return 0;
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    FILE *dummy_file = fopen("./dummy_file", "w");
    if (!dummy_file) {
        free(buffer);
        return 0;
    }

    test_curl_mvsprintf("%s", buffer, buffer);
    test_curl_mvfprintf(dummy_file, "%s", buffer, buffer);
    test_curl_mvsnprintf("%s", buffer, buffer);
    test_curl_mvprintf("%s", buffer, buffer);
    test_curl_mprintf("%s", buffer);

    fclose(dummy_file);
    free(buffer);
    return 0;
}