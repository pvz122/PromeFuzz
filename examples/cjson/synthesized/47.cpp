// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_SetValuestring at cJSON.c:403:21 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure the input data is null-terminated
    char *nullTerminatedData = (char *)malloc(Size + 1);
    if (!nullTerminatedData) return 0;
    memcpy(nullTerminatedData, Data, Size);
    nullTerminatedData[Size] = '\0';

    // Create a cJSON string object
    cJSON *jsonString = cJSON_CreateString(nullTerminatedData);
    if (!jsonString) {
        free(nullTerminatedData);
        return 0;
    }

    // Test cJSON_SetValuestring
    char *newValue = (char *)malloc(Size + 1);
    if (!newValue) {
        cJSON_Delete(jsonString);
        free(nullTerminatedData);
        return 0;
    }
    memcpy(newValue, Data, Size);
    newValue[Size] = '\0';
    cJSON_SetValuestring(jsonString, newValue);
    free(newValue);

    // Test cJSON_GetStringValue
    char *retrievedValue = cJSON_GetStringValue(jsonString);
    if (!retrievedValue) {
        cJSON_Delete(jsonString);
        free(nullTerminatedData);
        return 0;
    }

    // Create a cJSON object to add items to
    cJSON *jsonObject = cJSON_CreateObject();
    if (!jsonObject) {
        cJSON_Delete(jsonString);
        free(nullTerminatedData);
        return 0;
    }

    // Test cJSON_AddItemToObjectCS
    cJSON_AddItemToObjectCS(jsonObject, "key", jsonString);

    // Test cJSON_CreateStringReference
    cJSON *stringRef = cJSON_CreateStringReference(nullTerminatedData);
    if (stringRef) {
        cJSON_AddItemToObjectCS(jsonObject, "refKey", stringRef);
    }

    // Cleanup
    cJSON_Delete(jsonObject);
    free(nullTerminatedData);

    return 0;
}