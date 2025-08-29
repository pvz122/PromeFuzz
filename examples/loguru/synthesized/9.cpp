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

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize a buffer for suggest_log_path
    char buffer[256];
    const char* prefix = "./dummy_file";

    // Call current_dir
    const char* dir = loguru::current_dir();

    // Call home_dir
    const char* home = loguru::home_dir();

    // Call suggest_log_path
    loguru::suggest_log_path(prefix, buffer, sizeof(buffer));

    // Call create_directories
    const char* path = "./dummy_file/dir";
    bool created = loguru::create_directories(path);

    // Call add_file
    const char* filename = "./dummy_file/log.txt";
    bool added = loguru::add_file(filename, loguru::FileMode::Append, loguru::Verbosity_MAX);

    return 0;
}