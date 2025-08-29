// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_ParseWithOpts at cJSON.c:1099:23 in cJSON.h
// cJSON_PrintBuffered at cJSON.c:1285:22 in cJSON.h
// cJSON_Print at cJSON.c:1275:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1280:22 in cJSON.h
// cJSON_Minify at cJSON.c:2882:20 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
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
    cJSON *json = cJSON_ParseWithOpts(json_str, &parse_end, 1);
    if (json == nullptr) {
        free(json_str);
        return 0;
    }

    char *buffered_print = cJSON_PrintBuffered(json, 1024, 1);
    if (buffered_print != nullptr) {
        free(buffered_print);
    }

    char *print = cJSON_Print(json);
    if (print != nullptr) {
        free(print);
    }

    char *unformatted_print = cJSON_PrintUnformatted(json);
    if (unformatted_print != nullptr) {
        free(unformatted_print);
    }

    cJSON_Minify(json_str);

    cJSON_Delete(json);
    free(json_str);

    return 0;
}