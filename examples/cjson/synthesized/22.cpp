// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2567:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2083:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2742:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2742:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2019:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2077:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    char *key1 = (char *)malloc(5);
    char *key2 = (char *)malloc(5);
    if (!key1 || !key2) return 0;

    memcpy(key1, Data, 4);
    key1[4] = '\0';
    memcpy(key2, Data + 4, 4);
    key2[4] = '\0';

    cJSON *root = cJSON_CreateObject();
    cJSON *item1 = cJSON_CreateString("value1");
    cJSON *item2 = cJSON_CreateString("value2");
    cJSON *array1 = cJSON_CreateArray();
    cJSON *array2 = cJSON_CreateArray();

    if (!root || !item1 || !item2 || !array1 || !array2) {
        free(key1);
        free(key2);
        cJSON_Delete(root);
        cJSON_Delete(item1);
        cJSON_Delete(item2);
        cJSON_Delete(array1);
        cJSON_Delete(array2);
        return 0;
    }

    cJSON_AddItemToObjectCS(root, key1, item1);
    cJSON_AddItemToObjectCS(root, key2, item2);

    cJSON_AddItemToArray(array1, cJSON_Duplicate(item1, 1));
    cJSON_AddItemToArray(array2, cJSON_Duplicate(item2, 1));

    cJSON_AddItemToObject(root, key1, array1);
    cJSON_AddItemToObject(root, key2, array2);

    free(key1);
    free(key2);
    cJSON_Delete(root);

    return 0;
}