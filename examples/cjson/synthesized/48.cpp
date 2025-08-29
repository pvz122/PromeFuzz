// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2168:22 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_SetValuestring at cJSON.c:403:21 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create a string from the input data
    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';

    // Test cJSON_AddStringToObject
    cJSON_AddStringToObject(root, "key", input_str);

    // Test cJSON_CreateString
    cJSON *string_item = cJSON_CreateString(input_str);
    if (string_item) {
        cJSON_AddItemToObject(root, "string_item", string_item);
    }

    // Test cJSON_SetValuestring
    if (string_item) {
        cJSON_SetValuestring(string_item, input_str);
    }

    // Test cJSON_CreateStringReference
    cJSON *string_ref = cJSON_CreateStringReference(input_str);
    if (string_ref) {
        cJSON_AddItemToObject(root, "string_ref", string_ref);
    }

    // Test cJSON_GetStringValue
    if (string_item) {
        cJSON_GetStringValue(string_item);
    }

    // Clean up
    free(input_str);
    cJSON_Delete(root);

    return 0;
}