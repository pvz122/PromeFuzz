// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_mvaprintf at mprintf.c:1132:7 in mprintf.h
// curl_free at escape.c:208:6 in curl.h
// curl_mvsnprintf at mprintf.c:1070:5 in mprintf.h
// curl_mvprintf at mprintf.c:1215:5 in mprintf.h
// curl_getenv at getenv.c:77:7 in curl.h
// curl_free at escape.c:208:6 in curl.h
// curl_maprintf at mprintf.c:1150:7 in mprintf.h
// curl_free at escape.c:208:6 in curl.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/curl.h>
#include <curl/mprintf.h>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cstdarg>

static void test_curl_mvaprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *vformatted_str = curl_mvaprintf(format, args);
    if (vformatted_str) {
        curl_free(vformatted_str);
    }
    va_end(args);
}

static void test_curl_mvsnprintf(const char *format, ...) {
    char output[256];
    va_list args;
    va_start(args, format);
    curl_mvsnprintf(output, sizeof(output), format, args);
    va_end(args);
}

static void test_curl_mvprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    curl_mvprintf(format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz curl_getenv
    char *env_var = curl_getenv("TEST_ENV_VAR");
    if (env_var) {
        curl_free(env_var);
    }

    // Fuzz curl_maprintf
    char *formatted_str = curl_maprintf("Test format: %.*s", static_cast<int>(Size), Data);
    if (formatted_str) {
        curl_free(formatted_str);
    }

    // Fuzz curl_mvaprintf
    test_curl_mvaprintf("Test format: %s", "test");

    // Fuzz curl_mvsnprintf
    test_curl_mvsnprintf("Test format: %s", "test");

    // Fuzz curl_mvprintf
    test_curl_mvprintf("Test format: %s", "test");

    return 0;
}