// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddFalseToObject at cJSON.c:2132:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Duplicate at cJSON.c:2742:23 in cJSON.h
// cJSON_IsObject at cJSON.c:3010:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2326:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Add a false value to the object
    cJSON *falseItem = cJSON_AddFalseToObject(root, "falseKey");
    if (!falseItem) {
        cJSON_Delete(root);
        return 0;
    }

    // Duplicate the JSON object
    cJSON *duplicate = cJSON_Duplicate(root, (Data[0] & 1) ? 1 : 0);
    if (duplicate) {
        // Check if the duplicated item is an object
        cJSON_IsObject(duplicate);

        // Replace the false item with a new item
        cJSON *newItem = cJSON_CreateString("newValue");
        if (newItem) {
            cJSON_ReplaceItemViaPointer(root, falseItem, newItem);
            // Do not delete newItem here as it is now part of the root object
        }

        cJSON_Delete(duplicate);
    }

    // Check if the original item is invalid
    // falseItem is now invalid after replacement, so we skip this check to avoid use-after-free
    // cJSON_IsInvalid(falseItem);

    // Clean up
    cJSON_Delete(root);

    return 0;
}