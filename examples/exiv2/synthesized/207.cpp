// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::parseUint32 at types.cpp:560:10 in types.hpp
// Exiv2::parseInt64 at types.cpp:534:9 in types.hpp
// Exiv2::parseFloat at types.cpp:568:7 in types.hpp
// Exiv2::parseRational at types.cpp:590:10 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::stringTo at types.hpp:483:3 in types.hpp
// Exiv2::isHex at types.cpp:479:6 in types.hpp
// Exiv2::isHex at types.cpp:479:6 in types.hpp
// Exiv2::isHex at types.cpp:479:6 in types.hpp
// Exiv2::isHex at types.cpp:479:6 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_207(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    bool ok = false;

    // Test parseUint32
    Exiv2::parseUint32(input, ok);

    // Test parseInt64
    Exiv2::parseInt64(input, ok);

    // Test parseFloat
    Exiv2::parseFloat(input, ok);

    // Test parseRational
    Exiv2::parseRational(input, ok);

    // Test stringTo with different types
    Exiv2::stringTo<uint32_t>(input, ok);
    Exiv2::stringTo<int64_t>(input, ok);
    Exiv2::stringTo<float>(input, ok);
    Exiv2::stringTo<Exiv2::Rational>(input, ok);

    // Test isHex with different parameters
    Exiv2::isHex(input);
    Exiv2::isHex(input, 4);
    Exiv2::isHex(input, 0, "0x");
    Exiv2::isHex(input, 8, "0x");

    return 0;
}