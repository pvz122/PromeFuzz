// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::version at version.cpp:81:13 in version.hpp
// Exiv2::versionNumber at version.cpp:65:10 in version.hpp
// Exiv2::versionString at version.cpp:69:13 in version.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/version.hpp>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    // Call version functions in the specified order
    const char* version_cstr = Exiv2::version();
    (void)version_cstr; // Avoid unused variable warning

    uint32_t version_num = Exiv2::versionNumber();
    (void)version_num; // Avoid unused variable warning

    std::string version_str = Exiv2::versionString();
    (void)version_str; // Avoid unused variable warning

    return 0;
}