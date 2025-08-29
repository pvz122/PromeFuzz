// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1195:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2506:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1941:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1941:23 in cJSON.h
// cJSON_SetValuestring at cJSON.c:403:21 in cJSON.h
// cJSON_SetValuestring at cJSON.c:403:21 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    char *jsonStr = new char[Size + 1];
    memcpy(jsonStr, Data, Size);
    jsonStr[Size] = '\0';

    cJSON *root = cJSON_Parse(jsonStr);
    if (root == nullptr) {
        delete[] jsonStr;
        return 0;
    }

    cJSON *stringItem = cJSON_CreateString("fuzz_string");
    cJSON *stringRefItem = cJSON_CreateStringReference("fuzz_string_ref");

    cJSON_AddItemToObject(root, "key1", stringItem);
    cJSON_AddItemToObject(root, "key2", stringRefItem);

    cJSON *item1 = cJSON_GetObjectItem(root, "key1");
    cJSON *item2 = cJSON_GetObjectItem(root, "key2");

    if (item1 != nullptr) {
        cJSON_SetValuestring(item1, "new_fuzz_string");
    }

    if (item2 != nullptr) {
        cJSON_SetValuestring(item2, "new_fuzz_string_ref");
    }

    cJSON_Delete(root);
    delete[] jsonStr;

    return 0;
}