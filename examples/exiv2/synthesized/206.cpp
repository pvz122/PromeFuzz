// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::versionNumber at version.cpp:65:10 in version.hpp
// Exiv2::versionString at version.cpp:69:13 in version.hpp
// Exiv2::dumpLibraryInfo at version.cpp:198:13 in version.hpp
// Exiv2::testVersion at version.cpp:85:6 in version.hpp
// Exiv2::versionNumberHexString at version.cpp:75:13 in version.hpp
// Exiv2::version at version.cpp:81:13 in version.hpp
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
#include <fstream>
#include <vector>
#include <regex>

extern "C" int LLVMFuzzerTestOneInput_206(const uint8_t *Data, size_t Size) {
    // Call versionNumber
    (void)Exiv2::versionNumber();

    // Call versionString
    (void)Exiv2::versionString();

    // Call dumpLibraryInfo
    std::ofstream os("./dummy_file");
    std::vector<std::regex> patterns;
    try {
        patterns.emplace_back(".*");
    } catch (const std::regex_error&) {
        // Ignore regex errors
    }
    Exiv2::dumpLibraryInfo(os, patterns);
    os.close();

    // Call testVersion with some arbitrary version numbers
    (void)Exiv2::testVersion(0, 27, 0);

    // Call versionNumberHexString
    (void)Exiv2::versionNumberHexString();

    // Call version
    (void)Exiv2::version();

    return 0;
}