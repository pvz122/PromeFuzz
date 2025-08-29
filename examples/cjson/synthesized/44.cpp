// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_SetValuestring at cJSON.c:403:21 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy string from the input data
    char *dummy_string = (char *)malloc(Size + 1);
    if (!dummy_string) return 0;
    memcpy(dummy_string, Data, Size);
    dummy_string[Size] = '\0';

    // Create a cJSON string object
    cJSON *json_string = cJSON_CreateString(dummy_string);
    if (!json_string) {
        free(dummy_string);
        return 0;
    }

    // Test cJSON_SetValuestring
    cJSON_SetValuestring(json_string, dummy_string);

    // Test cJSON_CreateStringReference
    cJSON *string_ref = cJSON_CreateStringReference(dummy_string);
    if (string_ref) {
        // Test cJSON_AddItemToObjectCS
        cJSON *root = cJSON_CreateObject();
        if (root) {
            cJSON_AddItemToObjectCS(root, "key", string_ref);
            cJSON_Delete(root);
        }
    }

    // Test cJSON_GetStringValue
    char *retrieved_string = cJSON_GetStringValue(json_string);
    if (retrieved_string) {
        // Do nothing, just to ensure the function is called
    }

    // Clean up
    cJSON_Delete(json_string);
    free(dummy_string);

    return 0;
}