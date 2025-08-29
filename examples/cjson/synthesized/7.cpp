// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1195:23 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_GetObjectItemCaseSensitive at cJSON.c:1946:23 in cJSON.h
// cJSON_IsString at cJSON.c:2990:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:2980:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:2980:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    // Create a null-terminated string from the input data
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return 0;
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    // Parse the JSON string
    cJSON *json = cJSON_Parse(json_string);
    if (!json) {
        free(json_string);
        return 0;
    }

    // Get the error pointer (should be NULL if parsing succeeded)
    const char *error_ptr = cJSON_GetErrorPtr();

    // Retrieve various items from the JSON object
    cJSON *item1 = cJSON_GetObjectItemCaseSensitive(json, "key1");
    cJSON *item2 = cJSON_GetObjectItemCaseSensitive(json, "key2");
    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(json, "key3");
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    // Check if items are strings or numbers
    if (item1) cJSON_IsString(item1);
    if (item2) cJSON_IsNumber(item2);
    if (item3) cJSON_IsNumber(item3);

    // Clean up
    cJSON_Delete(json);
    free(json_string);

    return 0;
}