// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2098:26 in cJSON.h
// cJSON_AddItemReferenceToArray at cJSON.c:2088:26 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2262:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create a dummy JSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) {
        cJSON_Delete(root);
        return 0;
    }

    // Create a dummy JSON item
    cJSON *item = cJSON_CreateNumber(42);
    if (!item) {
        cJSON_Delete(root);
        cJSON_Delete(array);
        return 0;
    }

    // Extract a key from the input data
    char key[256];
    size_t key_len = Size > 256 ? 256 : Size;
    memcpy(key, Data, key_len);
    key[key_len - 1] = '\0';

    // Add item reference to the object
    cJSON_AddItemReferenceToObject(root, key, item);

    // Add item reference to the array
    cJSON_AddItemReferenceToArray(array, item);

    // Delete item from the array
    cJSON_DeleteItemFromArray(array, 0);

    // Delete item from the object
    cJSON_DeleteItemFromObject(root, key);

    // Clean up
    cJSON_Delete(root);
    cJSON_Delete(array);
    cJSON_Delete(item);

    return 0;
}