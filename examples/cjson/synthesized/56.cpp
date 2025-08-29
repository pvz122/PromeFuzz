// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1195:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1280:22 in cJSON.h
// cJSON_PrintBuffered at cJSON.c:1285:22 in cJSON.h
// cJSON_Print at cJSON.c:1275:22 in cJSON.h
// cJSON_PrintPreallocated at cJSON.c:1316:26 in cJSON.h
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

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a null-terminated string from the input data
    char *json_str = (char *)malloc(Size + 1);
    if (!json_str) return 0;
    memcpy(json_str, Data, Size);
    json_str[Size] = '\0';

    // Parse the JSON string into a cJSON object
    cJSON *json = cJSON_Parse(json_str);
    if (!json) {
        free(json_str);
        return 0;
    }

    // Test cJSON_PrintUnformatted
    char *unformatted = cJSON_PrintUnformatted(json);
    if (unformatted) free(unformatted);

    // Test cJSON_PrintBuffered
    char *buffered = cJSON_PrintBuffered(json, 1024, 0);
    if (buffered) free(buffered);

    // Test cJSON_Print
    char *printed = cJSON_Print(json);
    if (printed) free(printed);

    // Test cJSON_PrintPreallocated
    char buffer[1024];
    cJSON_PrintPreallocated(json, buffer, sizeof(buffer), 0);

    // Clean up
    cJSON_Delete(json);
    free(json_str);

    return 0;
}