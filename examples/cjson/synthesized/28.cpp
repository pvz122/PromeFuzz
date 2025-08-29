// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2098:26 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2108:22 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy cJSON object
    cJSON *object = cJSON_CreateObject();
    if (!object) return 0;

    // Create a dummy cJSON item
    cJSON *item = cJSON_CreateNumber(42);
    if (!item) {
        cJSON_Delete(object);
        return 0;
    }

    // Generate a key from the input data
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(item);
        cJSON_Delete(object);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Fuzz the API functions
    cJSON_AddItemReferenceToObject(object, key, item);
    cJSON_DeleteItemFromObject(object, key);
    cJSON_AddNullToObject(object, key);
    cJSON_DeleteItemFromObjectCaseSensitive(object, key);
    cJSON_AddItemToObject(object, key, item);

    // Cleanup
    free(key);
    cJSON_Delete(object); // Delete the object first

    return 0;
}