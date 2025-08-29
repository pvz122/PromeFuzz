// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_IsNumber at cJSON.c:2980:26 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2156:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_SetNumberHelper at cJSON.c:384:22 in cJSON.h
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
#include <cstddef>
#include <cstdint>
#include <cfloat>

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double num = *reinterpret_cast<const double*>(Data);

    // Test cJSON_CreateNumber
    cJSON *numItem = cJSON_CreateNumber(num);
    if (numItem != nullptr) {
        // Test cJSON_GetNumberValue
        double retrievedNum = cJSON_GetNumberValue(numItem);
        (void)retrievedNum; // Avoid unused variable warning

        // Test cJSON_IsNumber
        if (cJSON_IsNumber(numItem)) {
            // Test cJSON_AddNumberToObject
            cJSON *object = cJSON_CreateObject();
            if (object != nullptr) {
                cJSON_AddNumberToObject(object, "number", num);
                cJSON_Delete(object);
            }

            // Test cJSON_SetNumberHelper
            double setNum = cJSON_SetNumberHelper(numItem, num);
            (void)setNum; // Avoid unused variable warning
        }

        cJSON_Delete(numItem);
    }

    return 0;
}