// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::isBigEndianPlatform at image.cpp:180:13 in image.hpp
// Exiv2::Image::isLittleEndianPlatform at image.cpp:202:13 in image.hpp
// Exiv2::Image::byteSwap at image.cpp:227:17 in image.hpp
// Exiv2::Image::byteSwap at image.cpp:227:17 in image.hpp
// Exiv2::Image::byteSwap2 at image.cpp:251:17 in image.hpp
// Exiv2::Image::byteSwap4 at image.cpp:259:17 in image.hpp
// Exiv2::Image::byteSwap8 at image.cpp:270:17 in image.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    // Test isBigEndianPlatform and isLittleEndianPlatform
    bool isBigEndian = Exiv2::Image::isBigEndianPlatform();
    bool isLittleEndian = Exiv2::Image::isLittleEndianPlatform();

    // Test byteSwap
    if (Size >= sizeof(uint32_t)) {
        uint32_t value;
        memcpy(&value, Data, sizeof(uint32_t));
        Exiv2::Image::byteSwap(value, true);
        Exiv2::Image::byteSwap(value, false);
    }

    // Prepare DataBuf for byteSwap2, byteSwap4, byteSwap8
    Exiv2::DataBuf buf(Data, Size);
    bool bSwap = (Size % 2 == 0);

    // Test byteSwap2
    if (Size >= 2) {
        size_t offset = Size > 2 ? Size % (Size - 1) : 0;
        Exiv2::Image::byteSwap2(buf, offset, bSwap);
    }

    // Test byteSwap4
    if (Size >= 4) {
        size_t offset = Size > 4 ? Size % (Size - 3) : 0;
        Exiv2::Image::byteSwap4(buf, offset, bSwap);
    }

    // Test byteSwap8
    if (Size >= 8) {
        size_t offset = Size > 8 ? Size % (Size - 7) : 0;
        Exiv2::Image::byteSwap8(buf, offset, bSwap);
    }

    return 0;
}