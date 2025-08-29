// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::ec_to_text at loguru.cpp:1809:7 in loguru.hpp
// loguru::textprintf at loguru.cpp:448:7 in loguru.hpp
// loguru::init at loguru.cpp:598:7 in loguru.hpp
// loguru::log at loguru.cpp:1511:7 in loguru.hpp
// loguru::raw_log at loguru.cpp:1525:7 in loguru.hpp
// loguru::format_value at loguru.hpp:746:32 in loguru.hpp
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

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize loguru with proper argc/argv
    int argc = 1;
    char arg0[] = "./dummy_file";
    char* argv[] = {arg0, nullptr};
    loguru::init(argc, argv);

    // Test loguru::format_value
    long long value = 0;
    if (Size >= sizeof(long long)) {
        value = *reinterpret_cast<const long long*>(Data);
    }
    loguru::Text text1 = loguru::format_value(value);

    // Test loguru::textprintf
    loguru::Text text2 = loguru::textprintf();

    // Test loguru::log
    std::string format_str(reinterpret_cast<const char*>(Data), Size);
    loguru::log(loguru::Verbosity_INFO, "./dummy_file", 42, "%.*s", static_cast<int>(Size), Data);

    // Test loguru::ec_to_text
    std::string data_str(reinterpret_cast<const char*>(Data), Size);
    loguru::Text text4 = loguru::ec_to_text(data_str.c_str());

    // Test loguru::raw_log
    loguru::raw_log(loguru::Verbosity_INFO, "./dummy_file", 42, "%.*s", static_cast<int>(Size), Data);

    return 0;
}