// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::set_verbosity_to_name_callback at loguru.cpp:894:7 in loguru.hpp
// loguru::set_name_to_verbosity_callback at loguru.cpp:899:7 in loguru.hpp
// loguru::get_verbosity_name at loguru.cpp:937:14 in loguru.hpp
// loguru::get_verbosity_from_name at loguru.cpp:962:12 in loguru.hpp
// loguru::current_verbosity_cutoff at loguru.cpp:1014:12 in loguru.hpp
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

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Fuzz loguru::get_verbosity_name
    loguru::Verbosity verbosity = static_cast<loguru::Verbosity>(Data[0] % 10);
    const char* verbosity_name = loguru::get_verbosity_name(verbosity);

    // Fuzz loguru::current_verbosity_cutoff
    loguru::Verbosity cutoff = loguru::current_verbosity_cutoff();

    // Fuzz loguru::get_verbosity_from_name
    char name[Size + 1];
    memcpy(name, Data, Size);
    name[Size] = '\0';
    loguru::Verbosity parsed_verbosity = loguru::get_verbosity_from_name(name);

    // Fuzz loguru::set_name_to_verbosity_callback
    auto name_to_verbosity_callback = [](const char* name) -> loguru::Verbosity {
        return loguru::Verbosity(0);
    };
    loguru::set_name_to_verbosity_callback(name_to_verbosity_callback);

    // Fuzz loguru::set_verbosity_to_name_callback
    auto verbosity_to_name_callback = [](loguru::Verbosity verbosity) -> const char* {
        return "INFO";
    };
    loguru::set_verbosity_to_name_callback(verbosity_to_name_callback);

    return 0;
}