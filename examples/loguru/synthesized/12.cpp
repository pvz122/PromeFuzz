// This fuzz driver is generated for library loguru, aiming to fuzz the following functions:
// loguru::home_dir at loguru.cpp:708:14 in loguru.hpp
// loguru::current_dir at loguru.cpp:703:14 in loguru.hpp
// loguru::create_directories at loguru.cpp:758:7 in loguru.hpp
// loguru::suggest_log_path at loguru.cpp:727:7 in loguru.hpp
// loguru::add_file at loguru.cpp:788:7 in loguru.hpp
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

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Test loguru::current_dir
    const char* dir = loguru::current_dir();

    // Test loguru::create_directories
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "./dummy_file_%d", Data[0]);
    loguru::create_directories(file_path);

    // Test loguru::suggest_log_path
    char buff[256];
    loguru::suggest_log_path("prefix", buff, sizeof(buff));

    // Test loguru::add_file
    loguru::add_file("./dummy_file.log", loguru::FileMode::Append, loguru::Verbosity_MAX);

    // Test loguru::home_dir
    const char* home = loguru::home_dir();

    return 0;
}