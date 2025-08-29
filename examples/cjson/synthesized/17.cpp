// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2144:22 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2144:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return 0;
    }

    cJSON_bool boolean1 = (Data[0] & 1) ? 1 : 0;
    cJSON_bool boolean2 = (Data[0] & 2) ? 1 : 0;

    cJSON_AddBoolToObject(root, "bool1", boolean1);
    cJSON_AddBoolToObject(root, "bool2", boolean2);

    cJSON_Delete(root);

    return 0;
}