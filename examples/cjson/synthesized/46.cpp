// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddRawToObject at cJSON.c:2180:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2204:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_DetachItemFromObjectCaseSensitive at cJSON.c:2274:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a cJSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Generate a name and raw JSON string from the input data
    char *name = (char *)malloc(Size + 1);
    if (!name) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    // Add raw JSON to the object
    cJSON *rawItem = cJSON_AddRawToObject(root, name, name);
    if (!rawItem) {
        free(name);
        cJSON_Delete(root);
        return 0;
    }

    // Add an array to the object
    cJSON *arrayItem = cJSON_AddArrayToObject(root, name);
    if (!arrayItem) {
        free(name);
        cJSON_Delete(root);
        return 0;
    }

    // Delete an item from the object
    cJSON_DeleteItemFromObjectCaseSensitive(root, name);

    // Detach an item from the object
    cJSON *detachedItem = cJSON_DetachItemFromObjectCaseSensitive(root, name);
    if (detachedItem) {
        cJSON_Delete(detachedItem);
    }

    // Clean up
    free(name);
    cJSON_Delete(root);

    return 0;
}