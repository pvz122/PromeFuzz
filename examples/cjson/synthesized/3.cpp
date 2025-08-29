// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2168:22 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2204:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2156:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2156:22 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Print at cJSON.c:1275:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a root object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Add a string to the root object
    cJSON_AddStringToObject(root, "key1", "value1");

    // Add an array to the root object
    cJSON *array = cJSON_AddArrayToObject(root, "array");
    if (!array) {
        cJSON_Delete(root);
        return 0;
    }

    // Create a new object to add to the array
    cJSON *newObj = cJSON_CreateObject();
    if (!newObj) {
        cJSON_Delete(root);
        return 0;
    }

    // Add numbers to the new object
    cJSON_AddNumberToObject(newObj, "num1", 42.0);
    cJSON_AddNumberToObject(newObj, "num2", 3.14);

    // Add the new object to the array
    if (!cJSON_AddItemToArray(array, newObj)) {
        cJSON_Delete(root);
        return 0;
    }

    // Print the JSON object
    char *jsonStr = cJSON_Print(root);
    if (jsonStr) {
        free(jsonStr);
    }

    // Clean up
    cJSON_Delete(root);

    return 0;
}