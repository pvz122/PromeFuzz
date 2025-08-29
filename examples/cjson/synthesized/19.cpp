// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddRawToObject at cJSON.c:2180:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    // Create a cJSON object
    cJSON *jsonObj = cJSON_CreateObject();
    if (!jsonObj) {
        return 0;
    }

    // Prepare the name and raw JSON string
    char *name = (char *)malloc(1);
    if (!name) {
        cJSON_Delete(jsonObj);
        return 0;
    }
    name[0] = '\0';

    char *raw = (char *)malloc(Size);
    if (!raw) {
        free(name);
        cJSON_Delete(jsonObj);
        return 0;
    }
    memcpy(raw, Data, Size);
    raw[Size - 1] = '\0';

    // Add raw JSON to the object
    cJSON_AddRawToObject(jsonObj, name, raw);

    // Clean up
    free(name);
    free(raw);
    cJSON_Delete(jsonObj);

    return 0;
}