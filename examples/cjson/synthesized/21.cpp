// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2108:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cJSON *obj = cJSON_CreateObject();
    if (obj == NULL) {
        return 0;
    }

    char *name = (char *)malloc(Size + 1);
    if (name == NULL) {
        cJSON_Delete(obj);
        return 0;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    cJSON_AddNullToObject(obj, name);

    free(name);
    cJSON_Delete(obj);

    return 0;
}