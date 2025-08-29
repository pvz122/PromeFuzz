// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddFalseToObject at cJSON.c:2132:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (!json_object) {
        return 0;
    }

    // Generate a dummy name for the false value
    char name[256];
    for (size_t i = 0; i < Size && i < 255; ++i) {
        name[i] = Data[i];
    }
    name[Size < 255 ? Size : 255] = '\0';

    // Add a false value to the object
    cJSON_AddFalseToObject(json_object, name);

    // Clean up
    cJSON_Delete(json_object);

    return 0;
}