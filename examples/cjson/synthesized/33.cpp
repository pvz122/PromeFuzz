// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2292:26 in cJSON.h
// cJSON_AddItemReferenceToArray at cJSON.c:2088:26 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2375:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2326:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1857:19 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) return 0;

    // Create a dummy JSON item
    cJSON *item = cJSON_CreateNumber(42);
    if (!item) {
        cJSON_Delete(array);
        return 0;
    }

    // Create a dummy JSON replacement item
    cJSON *replacement = cJSON_CreateString("replacement");
    if (!replacement) {
        cJSON_Delete(array);
        cJSON_Delete(item);
        return 0;
    }

    // Generate an index from the input data
    int index = Data[0] % 10;

    // Fuzz cJSON_InsertItemInArray
    cJSON_InsertItemInArray(array, index, item);

    // Fuzz cJSON_AddItemReferenceToArray
    cJSON_AddItemReferenceToArray(array, item);

    // Fuzz cJSON_ReplaceItemInArray
    cJSON_ReplaceItemInArray(array, index, replacement);

    // Fuzz cJSON_ReplaceItemViaPointer
    cJSON *first_child = cJSON_GetArrayItem(array, 0);
    if (first_child) {
        cJSON_ReplaceItemViaPointer(array, first_child, replacement);
    }

    // Fuzz cJSON_GetArraySize
    cJSON_GetArraySize(array);

    // Clean up
    cJSON_Delete(array);
    // Do not delete item and replacement here as they are now part of the array
    // and will be deleted when the array is deleted.

    return 0;
}