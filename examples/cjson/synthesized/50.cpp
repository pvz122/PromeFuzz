// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_ParseWithOpts at cJSON.c:1099:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1280:22 in cJSON.h
// cJSON_IsString at cJSON.c:2990:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2950:26 in cJSON.h
// cJSON_IsRaw at cJSON.c:3020:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    char *json_str = (char *)malloc(Size + 1);
    if (json_str == nullptr) {
        return 0;
    }
    memcpy(json_str, Data, Size);
    json_str[Size] = '\0';

    const char *parse_end = nullptr;
    cJSON *json = cJSON_ParseWithOpts(json_str, &parse_end, true);
    if (json == nullptr) {
        free(json_str);
        return 0;
    }

    char *unformatted = cJSON_PrintUnformatted(json);
    if (unformatted != nullptr) {
        free(unformatted);
    }

    cJSON_IsString(json);
    cJSON_IsTrue(json);
    cJSON_IsRaw(json);

    cJSON_Delete(json);
    free(json_str);
    return 0;
}