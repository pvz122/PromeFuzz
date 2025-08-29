// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::parseInt64 at types.cpp:534:9 in types.hpp
// Exiv2::parseFloat at types.cpp:568:7 in types.hpp
// Exiv2::parseRational at types.cpp:590:10 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize XMP parser
    Exiv2::XmpParser::initialize();

    // Create input string from fuzzer data
    std::string input(reinterpret_cast<const char*>(Data), Size);

    bool ok = false;

    // Test parseInt64
    Exiv2::parseInt64(input, ok);

    // Test parseFloat
    Exiv2::parseFloat(input, ok);

    // Test parseRational
    Exiv2::parseRational(input, ok);

    return 0;
}