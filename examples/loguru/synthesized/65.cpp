// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::ec_to_text at loguru.cpp:1809:7 in loguru.hpp
// loguru::Text::c_str at loguru.hpp:285:15 in loguru.hpp
// loguru::Text::empty at loguru.hpp:286:8 in loguru.hpp
// loguru::textprintf at loguru.cpp:437:7 in loguru.hpp
// loguru::format_value at loguru.hpp:731:32 in loguru.hpp
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

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Test loguru::format_value
    char char_value = static_cast<char>(Data[0]);
    loguru::Text text1 = loguru::format_value(char_value);

    // Test loguru::Text::c_str
    const char* cstr = text1.c_str();

    // Test loguru::Text::empty
    bool is_empty = text1.empty();

    // Test loguru::textprintf with a safe format string
    const char* safe_format = "%c";
    loguru::Text text2 = loguru::textprintf(safe_format, char_value);

    // Test loguru::ec_to_text
    std::string data_str(reinterpret_cast<const char*>(Data), Size);
    loguru::Text text3 = loguru::ec_to_text(data_str.c_str());

    return 0;
}