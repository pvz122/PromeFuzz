// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::ec_to_text at loguru.cpp:1863:2 in loguru.hpp
// loguru::textprintf at loguru.cpp:448:7 in loguru.hpp
// loguru::log at loguru.cpp:1511:7 in loguru.hpp
// loguru::raw_log at loguru.cpp:1525:7 in loguru.hpp
// loguru::format_value at loguru.hpp:743:32 in loguru.hpp
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned int)) {
        return 0;
    }

    unsigned int value;
    memcpy(&value, Data, sizeof(unsigned int));

    // Fuzz loguru::format_value
    loguru::format_value(value);

    // Fuzz loguru::textprintf
    loguru::textprintf();

    // Fuzz loguru::ec_to_text
    loguru::ec_to_text(value);

    // Fuzz loguru::log
    loguru::log(loguru::Verbosity_INFO, "./dummy_file", 42, "Fuzz log message: %u", value);

    // Fuzz loguru::raw_log
    loguru::raw_log(loguru::Verbosity_INFO, "./dummy_file", 42, "Fuzz raw log message: %u", value);

    return 0;
}