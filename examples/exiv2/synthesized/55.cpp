// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::isStringType at image.cpp:148:13 in image.hpp
// Exiv2::Image::isRationalType at image.cpp:161:13 in image.hpp
// Exiv2::Image::byteSwap at image.cpp:240:17 in image.hpp
// Exiv2::Image::isLongLongType at image.cpp:158:13 in image.hpp
// Exiv2::Image::is2ByteType at image.cpp:164:13 in image.hpp
// Exiv2::Image::isShortType at image.cpp:152:13 in image.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint16_t)) return 0;

    // Extract type from input data
    uint16_t type = *reinterpret_cast<const uint16_t*>(Data);
    bool bSwap = (Size % 2 == 0);

    // Test isStringType
    (void)Exiv2::Image::isStringType(type);

    // Test isRationalType
    (void)Exiv2::Image::isRationalType(type);

    // Test byteSwap
    (void)Exiv2::Image::byteSwap(type, bSwap);

    // Test isLongLongType
    (void)Exiv2::Image::isLongLongType(type);

    // Test is2ByteType
    (void)Exiv2::Image::is2ByteType(type);

    // Test isShortType
    (void)Exiv2::Image::isShortType(type);

    return 0;
}