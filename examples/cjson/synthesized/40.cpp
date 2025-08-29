// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2539:23 in cJSON.h
// cJSON_AddRawToObject at cJSON.c:2180:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1280:22 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2286:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create a raw JSON string from the input data
    char *raw_json = (char *)malloc(Size + 1);
    if (!raw_json) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(raw_json, Data, Size);
    raw_json[Size] = '\0';

    // Create a raw cJSON item
    cJSON *raw_item = cJSON_CreateRaw(raw_json);
    if (raw_item) {
        // Add the raw item to the object
        cJSON_AddRawToObject(root, "raw_key", raw_json);

        // Print the object unformatted
        char *unformatted = cJSON_PrintUnformatted(root);
        if (unformatted) {
            free(unformatted);
        }

        // Delete the item from the object
        cJSON_DeleteItemFromObjectCaseSensitive(root, "raw_key");

        // Delete the raw item to prevent memory leak
        cJSON_Delete(raw_item);
    }

    // Clean up
    free(raw_json);
    cJSON_Delete(root);

    return 0;
}