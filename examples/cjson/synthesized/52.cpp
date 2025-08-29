// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2529:23 in cJSON.h
// cJSON_IsArray at cJSON.c:3000:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsArray at cJSON.c:3000:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a cJSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) return 0;

    // Add some items to the array
    for (size_t i = 0; i < Size; ++i) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(Data[i]));
    }

    // Test cJSON_CreateArrayReference
    cJSON *arrayRef = cJSON_CreateArrayReference(array);
    if (arrayRef) {
        cJSON_IsArray(arrayRef);
        cJSON_Delete(arrayRef);
    }

    // Test cJSON_IsArray
    cJSON_IsArray(array);

    // Test cJSON_CreateDoubleArray
    double *doubleArray = (double *)malloc(Size * sizeof(double));
    if (doubleArray) {
        for (size_t i = 0; i < Size; ++i) {
            doubleArray[i] = static_cast<double>(Data[i]);
        }
        cJSON *doubleJsonArray = cJSON_CreateDoubleArray(doubleArray, Size);
        if (doubleJsonArray) {
            cJSON_Delete(doubleJsonArray);
        }
        free(doubleArray);
    }

    // Test cJSON_DetachItemFromArray
    int index = Data[0] % cJSON_GetArraySize(array);
    cJSON *detachedItem = cJSON_DetachItemFromArray(array, index);
    if (detachedItem) {
        cJSON_Delete(detachedItem);
    }

    // Test cJSON_GetArraySize
    cJSON_GetArraySize(array);

    // Clean up
    cJSON_Delete(array);

    return 0;
}