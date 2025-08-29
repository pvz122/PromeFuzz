// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy cJSON array
    cJSON *array = cJSON_CreateArray();
    if (!array) return 0;

    // Create a dummy cJSON item
    cJSON *item = cJSON_CreateNumber((double)Data[0]);
    if (!item) {
        cJSON_Delete(array);
        return 0;
    }

    // Add the item to the array
    cJSON_AddItemToArray(array, item);

    // Get the size of the array
    cJSON_GetArraySize(array);

    // Clean up
    cJSON_Delete(array);

    return 0;
}