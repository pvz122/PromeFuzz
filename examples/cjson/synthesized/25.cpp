// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_ParseWithLength at cJSON.c:1200:23 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Parse the JSON data
    cJSON *json = cJSON_ParseWithLength(reinterpret_cast<const char*>(Data), Size);
    
    // Clean up the parsed JSON object
    if (json) {
        cJSON_Delete(json);
    }
    
    return 0;
}