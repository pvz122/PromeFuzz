// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_AddTrueToObject at cJSON.c:2120:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cJSON *root = cJSON_CreateObject();
    if (root == nullptr) {
        return 0;
    }

    const char *name = "fuzz_key";
    cJSON *true_item = cJSON_AddTrueToObject(root, name);
    if (true_item == nullptr) {
        cJSON_Delete(root);
        return 0;
    }

    cJSON_Delete(root);
    return 0;
}