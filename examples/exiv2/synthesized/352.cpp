// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::isRationalType at image.cpp:161:13 in image.hpp
// Exiv2::Image::isLongLongType at image.cpp:158:13 in image.hpp
// Exiv2::Image::is2ByteType at image.cpp:164:13 in image.hpp
// Exiv2::Image::is4ByteType at image.cpp:167:13 in image.hpp
// Exiv2::Image::isShortType at image.cpp:152:13 in image.hpp
// Exiv2::Image::is8ByteType at image.cpp:170:13 in image.hpp
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

extern "C" int LLVMFuzzerTestOneInput_352(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint16_t)) {
        return 0;
    }

    uint16_t type;
    memcpy(&type, Data, sizeof(uint16_t));

    // Test all the static type-checking functions
    Exiv2::Image::isRationalType(type);
    Exiv2::Image::isLongLongType(type);
    Exiv2::Image::is2ByteType(type);
    Exiv2::Image::is4ByteType(type);
    Exiv2::Image::isShortType(type);
    Exiv2::Image::is8ByteType(type);

    return 0;
}