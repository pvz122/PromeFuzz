// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::getUShort at types.cpp:246:10 in types.hpp
// Exiv2::toData at value.hpp:1388:15 in value.hpp
// Exiv2::us2Data at types.cpp:331:8 in types.hpp
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
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_473(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test getValue<uint16_t>
    if (Size >= 2) {
        uint16_t val = Exiv2::getValue<uint16_t>(Data, byteOrder);
        (void)val;
    }

    // Test getUShort with raw buffer (avoid Slice template issues)
    if (Size >= 2) {
        uint16_t ushort = Exiv2::getUShort(Data, byteOrder);
        (void)ushort;
    }

    // Test toData<uint16_t>
    if (Size >= 2) {
        Exiv2::byte buf[2];
        uint16_t value = *reinterpret_cast<const uint16_t*>(Data);
        size_t written = Exiv2::toData(buf, value, byteOrder);
        (void)written;
    }

    // Test us2Data
    if (Size >= 2) {
        Exiv2::byte buf[2];
        uint16_t value = *reinterpret_cast<const uint16_t*>(Data);
        size_t written = Exiv2::us2Data(buf, value, byteOrder);
        (void)written;
    }

    // Test getULongLong
    if (Size >= 8) {
        uint64_t ull = Exiv2::getULongLong(Data, byteOrder);
        (void)ull;
    }

    // Test ull2Data
    if (Size >= 8) {
        Exiv2::byte buf[8];
        uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
        size_t written = Exiv2::ull2Data(buf, value, byteOrder);
        (void)written;
    }

    return 0;
}