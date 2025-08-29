// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2463:23 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a string JSON element
    char *input_str = (char *)malloc(Size + 1);
    if (!input_str) {
        return 0;
    }
    memcpy(input_str, Data, Size);
    input_str[Size] = '\0';
    cJSON *json_str = cJSON_CreateString(input_str);
    free(input_str);

    // Create a number JSON element
    cJSON *json_num = cJSON_CreateNumber(42.0);

    // Get the number value from the JSON elements
    double num_val1 = cJSON_GetNumberValue(json_str);
    double num_val2 = cJSON_GetNumberValue(json_num);
    double num_val3 = cJSON_GetNumberValue(NULL);

    // Clean up
    cJSON_Delete(json_str);
    cJSON_Delete(json_num);

    return 0;
}