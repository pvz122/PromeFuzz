// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1355:17 in value.hpp
// Exiv2::getRational at types.cpp:290:10 in types.hpp
// Exiv2::toData at value.hpp:1428:15 in value.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::r2Data at types.cpp:404:8 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_152(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test getValue<Rational>
    try {
        Exiv2::Rational r = Exiv2::getValue<Exiv2::Rational>(buf, byteOrder);
        (void)r;
    } catch (...) {}

    // Test getRational
    try {
        Exiv2::Rational r = Exiv2::getRational(buf, byteOrder);
        (void)r;
    } catch (...) {}

    // Test toData<Rational>
    if (Size >= 16) {
        Exiv2::byte outBuf[8];
        Exiv2::Rational r(static_cast<int32_t>(Data[0]), static_cast<int32_t>(Data[1]));
        try {
            size_t bytesWritten = Exiv2::toData(outBuf, r, byteOrder);
            (void)bytesWritten;
        } catch (...) {}
    }

    // Test getULongLong
    try {
        uint64_t ull = Exiv2::getULongLong(buf, byteOrder);
        (void)ull;
    } catch (...) {}

    // Test r2Data
    if (Size >= 16) {
        Exiv2::byte outBuf[8];
        Exiv2::Rational r(static_cast<int32_t>(Data[0]), static_cast<int32_t>(Data[1]));
        try {
            size_t bytesWritten = Exiv2::r2Data(outBuf, r, byteOrder);
            (void)bytesWritten;
        } catch (...) {}
    }

    // Test ull2Data
    if (Size >= 8) {
        Exiv2::byte outBuf[8];
        uint64_t ull = *reinterpret_cast<const uint64_t*>(Data);
        try {
            size_t bytesWritten = Exiv2::ull2Data(outBuf, ull, byteOrder);
            (void)bytesWritten;
        } catch (...) {}
    }

    return 0;
}