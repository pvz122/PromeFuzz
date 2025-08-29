// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1195:23 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2281:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_Minify at cJSON.c:2882:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a mutable copy of the input data for cJSON_Minify
    char *json_data = (char *)malloc(Size + 1);
    if (!json_data) return 0;
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    // Create a cJSON object
    cJSON *json = cJSON_Parse(json_data);
    if (!json) {
        free(json_data);
        return 0;
    }

    // Generate a key from the input data
    char key[256];
    size_t key_len = Size % 256;
    if (key_len == 0) key_len = 1;
    memcpy(key, Data, key_len);
    key[key_len] = '\0';

    // Invoke the target functions in the specified order
    cJSON_DeleteItemFromObject(json, key);
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);
    cJSON_Minify(json_data);
    cJSON_Delete(json);  // Only call this once

    // Clean up
    free(json_data);

    return 0;
}