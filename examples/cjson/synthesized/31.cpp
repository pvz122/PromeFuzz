// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2168:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2156:22 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2108:22 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1941:23 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2216:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2108:22 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_DetachItemFromObject at cJSON.c:2267:23 in cJSON.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Add some items to the object
    cJSON_AddStringToObject(root, "key1", "value1");
    cJSON_AddNumberToObject(root, "key2", 42);
    cJSON_AddNullToObject(root, "key3");

    // Generate a key from the input data
    char key[256];
    size_t key_len = Size < 255 ? Size : 255;
    memcpy(key, Data, key_len);
    key[key_len] = '\0';

    // Fuzz cJSON_DeleteItemFromObject
    cJSON_DeleteItemFromObject(root, key);

    // Fuzz cJSON_DetachItemViaPointer
    cJSON *item = cJSON_GetObjectItem(root, "key1");
    if (item) {
        cJSON_DetachItemViaPointer(root, item);
        cJSON_Delete(item);
    }

    // Fuzz cJSON_AddNullToObject
    cJSON_AddNullToObject(root, key);

    // Fuzz cJSON_DeleteItemFromObjectCaseSensitive
    cJSON_DeleteItemFromObjectCaseSensitive(root, key);

    // Fuzz cJSON_DetachItemFromObject
    cJSON *detached_item = cJSON_DetachItemFromObject(root, key);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Clean up
    cJSON_Delete(root);

    return 0;
}