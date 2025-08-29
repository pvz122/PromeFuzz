// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2408:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    double num1 = static_cast<double>(Data[0]);
    double num2 = static_cast<double>(Data[Size - 1]);

    cJSON *root = cJSON_CreateObject();
    cJSON *numItem1 = cJSON_CreateNumber(num1);
    cJSON *numItem2 = cJSON_CreateNumber(num2);

    if (root && numItem1 && numItem2) {
        cJSON_AddItemToObject(root, "key1", numItem1);
        cJSON_ReplaceItemInObject(root, "key1", numItem2);
    }

    cJSON_Delete(root);
    return 0;
}