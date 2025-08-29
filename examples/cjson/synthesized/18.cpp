// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateFalse at cJSON.c:2441:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateObjectReference at cJSON.c:2518:23 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy string from the input data
    char *dummy_string = (char *)malloc(Size + 1);
    if (!dummy_string) return 0;
    memcpy(dummy_string, Data, Size);
    dummy_string[Size] = '\0';

    // Create a cJSON_False object
    cJSON *false_obj = cJSON_CreateFalse();
    if (false_obj) {
        cJSON_Delete(false_obj);
    }

    // Create a cJSON_String object
    cJSON *string_obj = cJSON_CreateString(dummy_string);
    if (string_obj) {
        cJSON_Delete(string_obj);
    }

    // Create a cJSON_Object
    cJSON *object_obj = cJSON_CreateObject();
    if (object_obj) {
        cJSON_Delete(object_obj);
    }

    // Create a cJSON_StringReference
    cJSON *string_ref_obj = cJSON_CreateStringReference(dummy_string);
    if (string_ref_obj) {
        cJSON_Delete(string_ref_obj);
    }

    // Create another cJSON_Object
    cJSON *another_object_obj = cJSON_CreateObject();
    if (another_object_obj) {
        // Create a cJSON_ObjectReference
        cJSON *object_ref_obj = cJSON_CreateObjectReference(another_object_obj);
        if (object_ref_obj) {
            cJSON_Delete(object_ref_obj);
        }
        cJSON_Delete(another_object_obj);
    }

    free(dummy_string);
    return 0;
}