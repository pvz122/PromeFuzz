// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::parseInt64 at types.cpp:534:9 in types.hpp
// Exiv2::parseFloat at types.cpp:568:7 in types.hpp
// Exiv2::parseRational at types.cpp:590:10 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/types.hpp>
#include <string>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_138(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    bool ok = false;

    // Test parseInt64
    Exiv2::parseInt64(input, ok);

    // Test parseFloat
    Exiv2::parseFloat(input, ok);

    // Test parseRational
    Exiv2::parseRational(input, ok);

    // Test stringTo (int)
    Exiv2::stringTo<int>(input, ok);

    // Test stringTo (float)
    Exiv2::stringTo<float>(input, ok);

    // Test toString (int)
    Exiv2::toString(42);

    // Test toString (float)
    Exiv2::toString(3.14f);

    return 0;
}