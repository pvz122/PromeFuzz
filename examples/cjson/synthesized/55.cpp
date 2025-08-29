// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_IsArray at cJSON.c:3000:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1857:19 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_CreateDoubleArray at cJSON.c:2659:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1857:19 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2252:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) return 0;

    // Add some items to the array
    for (size_t i = 0; i < Size; ++i) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(Data[i]));
    }

    // Test cJSON_IsArray
    cJSON_IsArray(array);

    // Test cJSON_GetArrayItem
    for (int i = 0; i < cJSON_GetArraySize(array); ++i) {
        cJSON_GetArrayItem(array, i);
    }

    // Test cJSON_CreateDoubleArray
    double *doubles = new double[Size];
    for (size_t i = 0; i < Size; ++i) {
        doubles[i] = static_cast<double>(Data[i]);
    }
    cJSON *doubleArray = cJSON_CreateDoubleArray(doubles, Size);
    delete[] doubles;
    if (doubleArray) {
        cJSON_Delete(doubleArray);
    }

    // Test cJSON_DetachItemFromArray
    for (int i = 0; i < cJSON_GetArraySize(array); ++i) {
        cJSON *detachedItem = cJSON_DetachItemFromArray(array, i);
        if (detachedItem) {
            cJSON_Delete(detachedItem);
        }
    }

    // Test cJSON_GetArraySize
    cJSON_GetArraySize(array);

    // Clean up
    cJSON_Delete(array);

    return 0;
}