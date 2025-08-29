// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1355:17 in value.hpp
// Exiv2::getRational at types.cpp:290:10 in types.hpp
// Exiv2::getDouble at types.cpp:308:8 in types.hpp
// Exiv2::toData at value.hpp:1428:15 in value.hpp
// Exiv2::floatToRationalCast at types.cpp:611:10 in types.hpp
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
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    if (size < 8) return 0;

    Exiv2::ByteOrder byteOrder = size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(data);

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

    // Test getDouble
    try {
        double d = Exiv2::getDouble(buf, byteOrder);
        (void)d;
    } catch (...) {}

    // Test toData<Rational>
    if (size >= 16) {
        Exiv2::byte outBuf[8];
        Exiv2::Rational r;
        r.first = *reinterpret_cast<const int32_t*>(data);
        r.second = *reinterpret_cast<const int32_t*>(data + 4);
        try {
            size_t bytesWritten = Exiv2::toData(outBuf, r, byteOrder);
            (void)bytesWritten;
        } catch (...) {}
    }

    // Test floatToRationalCast
    if (size >= 4) {
        float f = *reinterpret_cast<const float*>(data);
        try {
            Exiv2::Rational r = Exiv2::floatToRationalCast(f);
            (void)r;
        } catch (...) {}
    }

    // Test r2Data
    if (size >= 8) {
        Exiv2::byte outBuf[8];
        Exiv2::Rational r;
        r.first = *reinterpret_cast<const int32_t*>(data);
        r.second = *reinterpret_cast<const int32_t*>(data + 4);
        try {
            size_t bytesWritten = Exiv2::r2Data(outBuf, r, byteOrder);
            (void)bytesWritten;
        } catch (...) {}
    }

    return 0;
}