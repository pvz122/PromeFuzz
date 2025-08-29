// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_vmprintf at sqlite3.c:19076:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_vsnprintf at sqlite3.c:19125:18 in sqlite3.h
// sqlite3_str_vappendf at sqlite3.c:17988:17 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19100:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_snprintf at sqlite3.c:19140:18 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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
#include <cstdarg>

static void test_vmprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *str = sqlite3_vmprintf(format, args);
    va_end(args);
    if (str) sqlite3_free(str);
}

static void test_vsnprintf(char *buffer, int size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    sqlite3_vsnprintf(size, buffer, format, args);
    va_end(args);
}

static void test_str_vappendf(sqlite3_str *str_obj, const char *format, ...) {
    va_list args;
    va_start(args, format);
    sqlite3_str_vappendf(str_obj, format, args);
    va_end(args);
}

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a null-terminated copy of the input data
    char *input = new char[Size];
    memcpy(input, Data, Size - 1);
    input[Size - 1] = '\0';

    // Test sqlite3_mprintf
    char *str1 = sqlite3_mprintf("%s", input);
    if (str1) sqlite3_free(str1);

    // Test sqlite3_snprintf
    char buffer[256];
    sqlite3_snprintf(sizeof(buffer), buffer, "%s", input);

    // Test sqlite3_vmprintf
    test_vmprintf("%s", input);

    // Test sqlite3_vsnprintf
    test_vsnprintf(buffer, sizeof(buffer), "%s", input);

    // Test sqlite3_str_vappendf
    sqlite3_str *str_obj = sqlite3_str_new(nullptr);
    test_str_vappendf(str_obj, "%s", input);
    char *str = sqlite3_str_finish(str_obj);
    if (str) sqlite3_free(str);

    delete[] input;
    return 0;
}