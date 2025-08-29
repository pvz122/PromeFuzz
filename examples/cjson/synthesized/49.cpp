// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_Print at cJSON.c:1275:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringArray at cJSON.c:2699:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "cJSON.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a null-terminated string from the input data
    char *input_string = (char *)malloc(Size + 1);
    if (!input_string) return 0;
    memcpy(input_string, Data, Size);
    input_string[Size] = '\0';

    // Test cJSON_CreateString
    cJSON *json_string = cJSON_CreateString(input_string);
    if (json_string) {
        // Test cJSON_GetStringValue
        char *str_value = cJSON_GetStringValue(json_string);
        (void)str_value; // Avoid unused variable warning

        // Test cJSON_Print
        char *printed_json = cJSON_Print(json_string);
        if (printed_json) {
            free(printed_json);
        }

        cJSON_Delete(json_string);
    }

    // Test cJSON_CreateStringReference
    cJSON *json_string_ref = cJSON_CreateStringReference(input_string);
    if (json_string_ref) {
        cJSON_Delete(json_string_ref);
    }

    // Test cJSON_CreateStringArray
    const char *strings[] = {input_string};
    cJSON *json_string_array = cJSON_CreateStringArray(strings, 1);
    if (json_string_array) {
        cJSON_Delete(json_string_array);
    }

    free(input_string);
    return 0;
}