// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2742:23 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2252:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    // Create three arrays
    cJSON *array1 = cJSON_CreateArray();
    cJSON *array2 = cJSON_CreateArray();
    cJSON *array3 = cJSON_CreateArray();

    if (array1 && array2 && array3) {
        // Add items to the arrays
        cJSON_AddItemToArray(array1, cJSON_CreateNumber(1));
        cJSON_AddItemToArray(array2, cJSON_CreateNumber(2));
        cJSON_AddItemToArray(array3, cJSON_CreateNumber(3));

        // Duplicate array1
        cJSON *duplicatedArray = cJSON_Duplicate(array1, true);

        if (duplicatedArray) {
            // Detach an item from array2
            cJSON *detachedItem = cJSON_DetachItemFromArray(array2, 0);

            if (detachedItem) {
                // Clean up detached item
                cJSON_Delete(detachedItem);
            }

            // Clean up duplicated array
            cJSON_Delete(duplicatedArray);
        }

        // Clean up arrays
        cJSON_Delete(array1);
        cJSON_Delete(array2);
        cJSON_Delete(array3);
    }

    return 0;
}