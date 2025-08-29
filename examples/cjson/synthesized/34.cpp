// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateBool at cJSON.c:2452:23 in cJSON.h
// cJSON_IsBool at cJSON.c:2961:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2950:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2940:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON_bool boolean = Data[0] % 2;
    cJSON *bool_item = cJSON_CreateBool(boolean);
    if (bool_item == nullptr) return 0;

    cJSON_IsBool(bool_item);
    cJSON_IsTrue(bool_item);
    cJSON_IsFalse(bool_item);

    cJSON_Delete(bool_item);

    return 0;
}