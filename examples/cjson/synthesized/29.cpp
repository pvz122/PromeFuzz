// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1951:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_ReplaceItemInObjectCaseSensitive at cJSON.c:2413:26 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create a dummy item to add/replace
    cJSON *item = cJSON_CreateNumber(42);
    if (!item) {
        cJSON_Delete(root);
        return 0;
    }

    // Extract key from input data
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(root);
        cJSON_Delete(item);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Add item to object with case-sensitive key
    cJSON_AddItemToObjectCS(root, key, item);

    // Check if the item exists
    if (cJSON_HasObjectItem(root, key)) {
        // Replace the item
        cJSON *newItem = cJSON_CreateString("replaced");
        if (newItem) {
            cJSON_ReplaceItemInObjectCaseSensitive(root, key, newItem);
        }

        // Delete the item
        cJSON_DeleteItemFromObjectCaseSensitive(root, key);
    }

    // Delete the item from the object
    cJSON_DeleteItemFromObject(root, key);

    // Clean up
    free(key);
    cJSON_Delete(root);

    return 0;
}