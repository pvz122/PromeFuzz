// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::ec_to_text at loguru.cpp:1809:7 in loguru.hpp
// loguru::ec_to_text at loguru.cpp:1868:2 in loguru.hpp
// loguru::Text::c_str at loguru.hpp:285:15 in loguru.hpp
// loguru::Text::empty at loguru.hpp:286:8 in loguru.hpp
// loguru::textprintf at loguru.cpp:448:7 in loguru.hpp
// loguru::format_value at loguru.hpp:733:32 in loguru.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "loguru.hpp"
#include <cstdint>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) {
        return 0;
    }

    // Initialize float value from input data
    float float_value;
    std::memcpy(&float_value, Data, sizeof(float));

    // Test loguru::format_value
    loguru::Text text1 = loguru::format_value(float_value);

    // Test loguru::Text::c_str
    const char* cstr = text1.c_str();

    // Test loguru::Text::empty
    bool is_empty = text1.empty();

    // Test loguru::textprintf
    loguru::Text text2 = loguru::textprintf();

    // Ensure the input string is null-terminated
    std::string data_str(reinterpret_cast<const char*>(Data), Size);

    // Test loguru::ec_to_text
    loguru::Text text3 = loguru::ec_to_text(float_value);
    loguru::Text text4 = loguru::ec_to_text(data_str.c_str());

    return 0;
}