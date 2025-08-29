// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_str_new at sqlite3.c:19028:25 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
// sqlite3_str_appendall at sqlite3.c:18901:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19227:17 in sqlite3.h
// sqlite3_str_append at sqlite3.c:18884:17 in sqlite3.h
// sqlite3_str_value at sqlite3.c:18984:18 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:18962:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17301:17 in sqlite3.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3_str *str = sqlite3_str_new(nullptr);
    if (!str) return 0;

    // Use the first byte to determine the operation
    uint8_t operation = Data[0] % 5;
    const char *input = reinterpret_cast<const char *>(Data + 1);
    size_t input_size = Size - 1;

    // Ensure input is null-terminated
    char *null_terminated_input = static_cast<char *>(malloc(input_size + 1));
    if (!null_terminated_input) {
        sqlite3_free(str);
        return 0;
    }
    memcpy(null_terminated_input, input, input_size);
    null_terminated_input[input_size] = '\0';

    switch (operation) {
        case 0:
            sqlite3_str_appendall(str, null_terminated_input);
            break;
        case 1:
            sqlite3_str_appendf(str, "%.*s", static_cast<int>(input_size), null_terminated_input);
            break;
        case 2:
            sqlite3_str_append(str, null_terminated_input, static_cast<int>(input_size));
            break;
        case 3:
            sqlite3_str_value(str);
            break;
        case 4:
            char *result = sqlite3_str_finish(str);
            if (result) sqlite3_free(result);
            free(null_terminated_input);
            return 0;
    }

    char *result = sqlite3_str_finish(str);
    if (result) sqlite3_free(result);
    free(null_terminated_input);

    return 0;
}