// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddObjectToObject at cJSON.c:2192:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a new JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        return 0;
    }

    // Create a dummy name for the new object
    char name[256];
    size_t name_len = Size > 255 ? 255 : Size;
    memcpy(name, Data, name_len);
    name[name_len] = '\0';

    // Add a new JSON object to the root object
    cJSON *new_obj = cJSON_AddObjectToObject(root, name);
    if (new_obj == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Clean up
    cJSON_Delete(root);

    return 0;
}