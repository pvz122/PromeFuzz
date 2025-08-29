// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateDoubleArray at cJSON.c:2659:23 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1857:19 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2262:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2252:23 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2) return 0;

    // Create a double array from the input data
    double *numbers = (double *)Data;
    int count = Size / sizeof(double);
    cJSON *jsonArray = cJSON_CreateDoubleArray(numbers, count);
    if (!jsonArray) return 0;

    // Test cJSON_GetArraySize
    int arraySize = cJSON_GetArraySize(jsonArray);

    // Test cJSON_GetArrayItem
    for (int i = 0; i < arraySize; ++i) {
        cJSON *item = cJSON_GetArrayItem(jsonArray, i);
        if (!item) continue;
    }

    // Test cJSON_DeleteItemFromArray
    if (arraySize > 0) {
        int indexToDelete = *Data % arraySize;
        cJSON_DeleteItemFromArray(jsonArray, indexToDelete);
    }

    // Test cJSON_DetachItemFromArray
    if (arraySize > 0) {
        int indexToDetach = *Data % arraySize;
        cJSON *detachedItem = cJSON_DetachItemFromArray(jsonArray, indexToDetach);
        if (detachedItem) {
            cJSON_Delete(detachedItem);
        }
    }

    cJSON_Delete(jsonArray);
    return 0;
}