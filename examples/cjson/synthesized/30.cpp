// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_ReplaceItemInObjectCaseSensitive at cJSON.c:2413:26 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1951:26 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create a dummy key and value
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    cJSON *value = cJSON_CreateString("value");
    if (!value) {
        free(key);
        cJSON_Delete(root);
        return 0;
    }

    // Add item to object
    cJSON_AddItemToObjectCS(root, key, value);

    // Replace item in object
    cJSON *new_value = cJSON_CreateString("new_value");
    if (new_value) {
        cJSON_ReplaceItemInObjectCaseSensitive(root, key, new_value);
    }

    // Check if item exists
    cJSON_HasObjectItem(root, key);

    // Delete item from object
    cJSON_DeleteItemFromObject(root, key);

    // Delete item from object case sensitive
    cJSON_DeleteItemFromObjectCaseSensitive(root, key);

    // Cleanup
    free(key);
    cJSON_Delete(root);

    return 0;
}