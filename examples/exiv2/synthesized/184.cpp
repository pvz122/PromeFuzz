// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::isRationalType at image.cpp:161:13 in image.hpp
// Exiv2::Image::isPrintXMP at image.cpp:173:13 in image.hpp
// Exiv2::Image::is4ByteType at image.cpp:167:13 in image.hpp
// Exiv2::Image::is2ByteType at image.cpp:164:13 in image.hpp
// Exiv2::Image::isPrintICC at image.cpp:176:13 in image.hpp
// Exiv2::Image::isLongType at image.cpp:155:13 in image.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/image.hpp>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_184(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Extract a uint16_t type from the input data
    uint16_t type = 0;
    if (Size >= sizeof(type)) {
        memcpy(&type, Data, sizeof(type));
    } else {
        type = static_cast<uint16_t>(Data[0]);
    }

    // Extract a PrintStructureOption from the input data safely
    Exiv2::PrintStructureOption option = Exiv2::PrintStructureOption::kpsNone;
    if (Size > sizeof(type)) {
        option = static_cast<Exiv2::PrintStructureOption>(Data[sizeof(type)] % 6);
    }

    // Call the target API functions
    (void)Exiv2::Image::isRationalType(type);
    (void)Exiv2::Image::isPrintXMP(type, option);
    (void)Exiv2::Image::is4ByteType(type);
    (void)Exiv2::Image::is2ByteType(type);
    (void)Exiv2::Image::isPrintICC(type, option);
    (void)Exiv2::Image::isLongType(type);

    return 0;
}