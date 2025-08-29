// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_CreateObjectReference at cJSON.c:2518:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    double num;
    memcpy(&num, Data, sizeof(double));

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return 0;
    }

    cJSON *number = cJSON_CreateNumber(num);
    if (!number) {
        cJSON_Delete(root);
        return 0;
    }

    cJSON_AddItemToObjectCS(root, "number", number);

    cJSON *ref = cJSON_CreateObjectReference(root);
    if (!ref) {
        cJSON_Delete(root);
        return 0;
    }

    cJSON_Delete(ref);
    cJSON_Delete(root);

    return 0;
}