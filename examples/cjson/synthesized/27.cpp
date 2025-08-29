// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1857:19 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
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
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a JSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) return 0;

    // Create some JSON items
    cJSON *item1 = cJSON_CreateString("item1");
    cJSON *item2 = cJSON_CreateNumber(42);
    cJSON *item3 = cJSON_CreateObject();
    cJSON *item4 = cJSON_CreateArray();

    if (!item1 || !item2 || !item3 || !item4) {
        cJSON_Delete(array);
        return 0;
    }

    // Add items to the array
    cJSON_AddItemToArray(array, item1);
    cJSON_AddItemToArray(array, item2);
    cJSON_AddItemToArray(array, item3);
    cJSON_AddItemToArray(array, item4);

    // Generate a random index
    int index = Data[0] % (cJSON_GetArraySize(array) + 1);

    // Create a new item to insert/replace
    cJSON *newItem = cJSON_CreateString("newItem");
    if (!newItem) {
        cJSON_Delete(array);
        return 0;
    }

    // Fuzz the API functions
    cJSON_InsertItemInArray(array, index, newItem);
    cJSON_AddItemReferenceToArray(array, newItem);
    cJSON_ReplaceItemInArray(array, index, newItem);
    cJSON_ReplaceItemViaPointer(array, cJSON_GetArrayItem(array, index), newItem);
    cJSON_GetArraySize(array);

    // Cleanup
    cJSON_Delete(array);

    return 0;
}