// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2529:23 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double num = *reinterpret_cast<const double*>(Data);

    cJSON *array = cJSON_CreateArray();
    if (!array) {
        return 0;
    }

    cJSON *number = cJSON_CreateNumber(num);
    if (!number) {
        cJSON_Delete(array);
        return 0;
    }

    if (!cJSON_AddItemToArray(array, number)) {
        cJSON_Delete(array);
        cJSON_Delete(number);
        return 0;
    }

    cJSON *arrayRef = cJSON_CreateArrayReference(array);
    if (!arrayRef) {
        cJSON_Delete(array);
        return 0;
    }

    cJSON_Delete(array);
    cJSON_Delete(arrayRef);

    return 0;
}