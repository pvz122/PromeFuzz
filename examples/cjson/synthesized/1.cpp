// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNull at cJSON.c:2419:23 in cJSON.h
// cJSON_CreateNull at cJSON.c:2419:23 in cJSON.h
// cJSON_CreateNull at cJSON.c:2419:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_free at cJSON.c:3160:20 in cJSON.h
// cJSON_free at cJSON.c:3160:20 in cJSON.h
// cJSON_free at cJSON.c:3160:20 in cJSON.h
// cJSON_free at cJSON.c:3160:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    cJSON *null1 = cJSON_CreateNull();
    cJSON *null2 = cJSON_CreateNull();
    cJSON *null3 = cJSON_CreateNull();
    cJSON *array = cJSON_CreateArray();

    if (array && null1 && null2 && null3) {
        cJSON_AddItemToArray(array, null1);
        cJSON_AddItemToArray(array, null2);
        cJSON_AddItemToArray(array, null3);
    }

    cJSON_free(array);
    cJSON_free(null1);
    cJSON_free(null2);
    cJSON_free(null3);
    return 0;
}