// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1365:15 in value.hpp
// Exiv2::getDouble at types.cpp:308:8 in types.hpp
// Exiv2::getDouble at types.cpp:308:8 in types.hpp
// Exiv2::toData at value.hpp:1444:15 in value.hpp
// Exiv2::d2Data at types.cpp:422:8 in types.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
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
#include <cstdint>
#include <cstring>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

extern "C" int LLVMFuzzerTestOneInput_329(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test getValue<double>
    try {
        Exiv2::getValue<double>(buf, byteOrder);
    } catch (...) {}

    // Test getDouble
    try {
        Exiv2::getDouble(buf, byteOrder);
    } catch (...) {}

    if (Size >= 16) {
        Exiv2::byte writeBuf[8];
        double dValue = Exiv2::getDouble(buf, byteOrder);

        // Test toData<double>
        try {
            Exiv2::toData(writeBuf, dValue, byteOrder);
        } catch (...) {}

        // Test d2Data
        try {
            Exiv2::d2Data(writeBuf, dValue, byteOrder);
        } catch (...) {}

        // Test getULongLong
        try {
            Exiv2::getULongLong(buf, byteOrder);
        } catch (...) {}

        uint64_t ullValue = Exiv2::getULongLong(buf, byteOrder);

        // Test ull2Data
        try {
            Exiv2::ull2Data(writeBuf, ullValue, byteOrder);
        } catch (...) {}
    }

    return 0;
}