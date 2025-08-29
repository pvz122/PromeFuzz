// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateIntArray at cJSON.c:2579:23 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2619:23 in cJSON.h
// cJSON_CreateStringArray at cJSON.c:2699:23 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    int count = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    if (count <= 0 || Size < static_cast<size_t>(count) * sizeof(int)) {
        return 0;
    }

    int *intArray = new int[count];
    float *floatArray = new float[count];
    char **stringArray = new char*[count];

    for (int i = 0; i < count; ++i) {
        intArray[i] = *reinterpret_cast<const int*>(Data);
        floatArray[i] = static_cast<float>(intArray[i]);
        stringArray[i] = new char[sizeof(int) + 1];
        std::memcpy(stringArray[i], Data, sizeof(int));
        stringArray[i][sizeof(int)] = '\0';
        Data += sizeof(int);
        Size -= sizeof(int);
    }

    cJSON *intJsonArray = cJSON_CreateIntArray(intArray, count);
    cJSON *floatJsonArray = cJSON_CreateFloatArray(floatArray, count);
    cJSON *stringJsonArray = cJSON_CreateStringArray(const_cast<const char**>(stringArray), count);

    if (intJsonArray) {
        for (int i = 0; i < count; ++i) {
            cJSON_GetArrayItem(intJsonArray, i);
        }
        cJSON_Delete(intJsonArray);
    }

    if (floatJsonArray) {
        for (int i = 0; i < count; ++i) {
            cJSON_GetArrayItem(floatJsonArray, i);
        }
        cJSON_Delete(floatJsonArray);
    }

    if (stringJsonArray) {
        for (int i = 0; i < count; ++i) {
            cJSON_GetArrayItem(stringJsonArray, i);
        }
        cJSON_Delete(stringJsonArray);
    }

    for (int i = 0; i < count; ++i) {
        delete[] stringArray[i];
    }
    delete[] intArray;
    delete[] floatArray;
    delete[] stringArray;

    return 0;
}