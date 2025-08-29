// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1345:16 in value.hpp
// Exiv2::s2Data at types.cpp:378:8 in types.hpp
// Exiv2::getShort at types.cpp:276:9 in types.hpp
// Exiv2::toData at value.hpp:1412:15 in value.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::r2Data at types.cpp:404:8 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_215(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 == 0 ? Exiv2::littleEndian : Exiv2::bigEndian;
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test getValue
    try {
        Exiv2::getValue<int16_t>(buf, byteOrder);
    } catch (...) {}

    // Test s2Data
    if (Size >= 2) {
        Exiv2::byte s2Buf[2];
        int16_t s = static_cast<int16_t>(Data[0] << 8 | Data[1]);
        Exiv2::s2Data(s2Buf, s, byteOrder);
    }

    // Test getShort
    try {
        Exiv2::getShort(buf, byteOrder);
    } catch (...) {}

    // Test toData
    if (Size >= 2) {
        Exiv2::byte toDataBuf[2];
        int16_t t = static_cast<int16_t>(Data[0] << 8 | Data[1]);
        Exiv2::toData(toDataBuf, t, byteOrder);
    }

    // Test getULongLong
    if (Size >= 8) {
        try {
            Exiv2::getULongLong(buf, byteOrder);
        } catch (...) {}
    }

    // Test r2Data
    if (Size >= 8) {
        Exiv2::byte r2Buf[8];
        Exiv2::Rational r = {static_cast<int32_t>(Data[0] << 24 | Data[1] << 16 | Data[2] << 8 | Data[3]),
                            static_cast<int32_t>(Data[4] << 24 | Data[5] << 16 | Data[6] << 8 | Data[7])};
        Exiv2::r2Data(r2Buf, r, byteOrder);
    }

    return 0;
}