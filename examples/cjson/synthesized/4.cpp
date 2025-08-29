// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1195:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_IsString at cJSON.c:2990:26 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2950:26 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_Duplicate at cJSON.c:2742:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_Compare at cJSON.c:3030:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON string
    char *json_str = new char[Size + 1];
    memcpy(json_str, Data, Size);
    json_str[Size] = '\0';

    // Parse the JSON string
    cJSON *json = cJSON_Parse(json_str);
    if (!json) {
        delete[] json_str;
        return 0;
    }

    // Perform the sequence of API calls
    cJSON *item1 = cJSON_GetObjectItemCaseSensitive(json, "key1");
    cJSON_IsString(item1);

    cJSON *item2 = cJSON_GetObjectItemCaseSensitive(json, "key2");
    cJSON_IsTrue(item2);

    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(json, "key3");
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    cJSON *duplicate = cJSON_Duplicate(json, true);

    cJSON *item5 = cJSON_GetObjectItemCaseSensitive(duplicate, "key5");
    cJSON *item6 = cJSON_GetObjectItemCaseSensitive(duplicate, "key6");

    cJSON_Compare(json, duplicate, true);

    // Clean up
    cJSON_Delete(json);
    cJSON_Delete(duplicate);
    delete[] json_str;

    return 0;
}