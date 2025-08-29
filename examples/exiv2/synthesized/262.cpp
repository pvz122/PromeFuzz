// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::isBigEndianPlatform at image.cpp:180:13 in image.hpp
// Exiv2::Image::isLittleEndianPlatform at image.cpp:202:13 in image.hpp
// Exiv2::Image::byteSwap at image.cpp:212:17 in image.hpp
// Exiv2::Image::byteSwap at image.cpp:212:17 in image.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::byteSwap2 at image.cpp:251:17 in image.hpp
// Exiv2::Image::byteSwap2 at image.cpp:251:17 in image.hpp
// Exiv2::Image::byteSwap4 at image.cpp:259:17 in image.hpp
// Exiv2::Image::byteSwap4 at image.cpp:259:17 in image.hpp
// Exiv2::Image::byteSwap8 at image.cpp:270:17 in image.hpp
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
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_262(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    // Test isBigEndianPlatform and isLittleEndianPlatform
    bool isBigEndian = Exiv2::Image::isBigEndianPlatform();
    bool isLittleEndian = Exiv2::Image::isLittleEndianPlatform();

    // Test byteSwap with various values and swap flags
    uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
    Exiv2::Image::byteSwap(value, true);
    Exiv2::Image::byteSwap(value, false);

    // Prepare DataBuf for byteSwap2, byteSwap4, byteSwap8
    Exiv2::DataBuf buf(Size);
    if (Size > buf.size()) {
        Size = buf.size();
    }
    std::memcpy(buf.data(), Data, Size);

    // Test byteSwap2 with various offsets and swap flags
    if (Size >= 2) {
        size_t offset = Data[0] % (Size - 1);
        Exiv2::Image::byteSwap2(buf, offset, true);
        Exiv2::Image::byteSwap2(buf, offset, false);
    }

    // Test byteSwap4 with various offsets and swap flags
    if (Size >= 4) {
        size_t offset = Data[0] % (Size - 3);
        Exiv2::Image::byteSwap4(buf, offset, true);
        Exiv2::Image::byteSwap4(buf, offset, false);
    }

    // Test byteSwap8 with various offsets and swap flags
    if (Size >= 8) {
        size_t offset = Data[0] % (Size - 7);
        Exiv2::Image::byteSwap8(buf, offset, true);
        Exiv2::Image::byteSwap8(buf, offset, false);
    }

    return 0;
}