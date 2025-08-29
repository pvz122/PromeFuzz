// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2108:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2216:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_malloc at cJSON.c:3155:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Add a null item to the object
    cJSON *null_item = cJSON_AddNullToObject(root, "null_key");
    if (!null_item) {
        cJSON_Delete(root);
        return 0;
    }

    // Create a dummy key from the input data
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Test cJSON_DetachItemViaPointer first to avoid use-after-free
    cJSON *detached_item = cJSON_DetachItemViaPointer(root, null_item);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Test cJSON_DeleteItemFromObject
    cJSON_DeleteItemFromObject(root, key);

    // Test cJSON_DeleteItemFromObjectCaseSensitive
    cJSON_DeleteItemFromObjectCaseSensitive(root, key);

    // Test cJSON_malloc
    void *allocated_memory = cJSON_malloc(Size);
    if (allocated_memory) {
        free(allocated_memory);
    }

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}