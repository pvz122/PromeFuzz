// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsString at cJSON.c:2990:26 in cJSON.h
// cJSON_IsArray at cJSON.c:3000:26 in cJSON.h
// cJSON_IsInvalid at cJSON.c:2930:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2970:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:2980:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy cJSON item with type based on input data
    cJSON item;
    item.type = Data[0] % 6; // 0: Invalid, 1: Null, 2: Number, 3: String, 4: Array, 5: Object
    item.valuestring = nullptr;
    item.valuedouble = 0.0;

    // Call the target functions
    cJSON_IsString(&item);
    cJSON_IsArray(&item);
    cJSON_IsInvalid(&item);
    cJSON_IsNull(&item);
    cJSON_IsNumber(&item);

    return 0;
}