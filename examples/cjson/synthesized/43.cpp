// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateBool at cJSON.c:2452:23 in cJSON.h
// cJSON_IsBool at cJSON.c:2961:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2950:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2940:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2489:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsString at cJSON.c:2990:26 in cJSON.h
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
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a cJSON object with a boolean value based on the first byte of input
    cJSON_bool boolean = Data[0] % 2;
    cJSON *bool_item = cJSON_CreateBool(boolean);
    if (bool_item == nullptr) return 0;

    // Test cJSON_IsBool function
    cJSON_IsBool(bool_item);

    // Test cJSON_IsTrue function
    cJSON_IsTrue(bool_item);

    // Test cJSON_IsFalse function
    cJSON_IsFalse(bool_item);

    // Create a cJSON object with a string value
    std::string input_string(reinterpret_cast<const char*>(Data), Size);
    cJSON *string_item = cJSON_CreateString(input_string.c_str());
    if (string_item == nullptr) {
        cJSON_Delete(bool_item);
        return 0;
    }

    // Test cJSON_IsString function
    cJSON_IsString(string_item);

    // Clean up
    cJSON_Delete(bool_item);
    cJSON_Delete(string_item);

    return 0;
}