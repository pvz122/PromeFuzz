// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_error at sqlite3.c:77859:17 in sqlite3.h
// sqlite3_result_value at sqlite3.c:78009:17 in sqlite3.h
// sqlite3_result_text at sqlite3.c:77939:17 in sqlite3.h
// sqlite3_malloc at sqlite3.c:17226:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_result_blob at sqlite3.c:77816:17 in sqlite3.h
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

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3_context *context = nullptr;
    sqlite3_value *value = nullptr;

    // Fuzz sqlite3_result_error
    const char *error_msg = reinterpret_cast<const char *>(Data);
    int error_len = Size > 100 ? 100 : Size;
    sqlite3_result_error(context, error_msg, error_len);

    // Fuzz sqlite3_result_value
    sqlite3_result_value(context, value);

    // Fuzz sqlite3_result_text
    const char *text = reinterpret_cast<const char *>(Data);
    int text_len = Size > 100 ? 100 : Size;
    sqlite3_result_text(context, text, text_len, SQLITE_TRANSIENT);

    // Fuzz sqlite3_malloc
    int malloc_size = Size > 100 ? 100 : Size;
    void *allocated_memory = sqlite3_malloc(malloc_size);
    if (allocated_memory) {
        sqlite3_free(allocated_memory);
    }

    // Fuzz sqlite3_result_blob
    const void *blob = reinterpret_cast< const void *>(Data);
    int blob_len = Size > 100 ? 100 : Size;
    sqlite3_result_blob(context, blob, blob_len, SQLITE_TRANSIENT);

    return 0;
}