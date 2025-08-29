// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2579:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1899:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a cJSON object
    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    // Create an integer array
    int numbers[10];
    for (int i = 0; i < 10; i++) {
        numbers[i] = i;
    }
    cJSON *intArray = cJSON_CreateIntArray(numbers, 10);
    if (!intArray) {
        cJSON_Delete(root);
        return 0;
    }

    // Get an item from the array
    cJSON *arrayItem = cJSON_GetArrayItem(intArray, 0);
    if (!arrayItem) {
        cJSON_Delete(intArray);
        cJSON_Delete(root);
        return 0;
    }

    // Add the integer array to the root object
    if (!cJSON_AddItemToObject(root, "intArray", intArray)) {
        cJSON_Delete(intArray);
        cJSON_Delete(root);
        return 0;
    }

    // Create another cJSON object
    cJSON *nestedObj = cJSON_CreateObject();
    if (!nestedObj) {
        cJSON_Delete(root);
        return 0;
    }

    // Create a string and add it to the nested object
    cJSON *stringItem = cJSON_CreateString("testString");
    if (!stringItem) {
        cJSON_Delete(nestedObj);
        cJSON_Delete(root);
        return 0;
    }
    if (!cJSON_AddItemToObject(nestedObj, "string", stringItem)) {
        cJSON_Delete(stringItem);
        cJSON_Delete(nestedObj);
        cJSON_Delete(root);
        return 0;
    }

    // Add the nested object to the root object
    if (!cJSON_AddItemToObject(root, "nestedObj", nestedObj)) {
        cJSON_Delete(nestedObj);
        cJSON_Delete(root);
        return 0;
    }

    // Create another cJSON object
    cJSON *anotherNestedObj = cJSON_CreateObject();
    if (!anotherNestedObj) {
        cJSON_Delete(root);
        return 0;
    }

    // Create another string and add it to the another nested object
    cJSON *anotherStringItem = cJSON_CreateString("anotherTestString");
    if (!anotherStringItem) {
        cJSON_Delete(anotherNestedObj);
        cJSON_Delete(root);
        return 0;
    }
    if (!cJSON_AddItemToObject(anotherNestedObj, "anotherString", anotherStringItem)) {
        cJSON_Delete(anotherStringItem);
        cJSON_Delete(anotherNestedObj);
        cJSON_Delete(root);
        return 0;
    }

    // Add the another nested object to the root object
    if (!cJSON_AddItemToObject(root, "anotherNestedObj", anotherNestedObj)) {
        cJSON_Delete(anotherNestedObj);
        cJSON_Delete(root);
        return 0;
    }

    // Clean up
    cJSON_Delete(root);

    return 0;
}