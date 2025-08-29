// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1335:17 in value.hpp
// Exiv2::getULong at types.cpp:250:10 in types.hpp
// Exiv2::getULong at types.cpp:250:10 in types.hpp
// Exiv2::toData at value.hpp:1396:15 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test getValue<uint32_t>
    if (Size >= 4) {
        uint32_t val1 = Exiv2::getValue<uint32_t>(Data, byteOrder);
        (void)val1;
    }

    // Test getULong
    if (Size >= 4) {
        uint32_t val2 = Exiv2::getULong(Data, byteOrder);
        (void)val2;
    }

    // Test toData<uint32_t>
    if (Size >= 4) {
        Exiv2::byte buf1[4];
        uint32_t val3 = Exiv2::getULong(Data, byteOrder);
        Exiv2::toData(buf1, val3, byteOrder);
    }

    // Test d2Data
    if (Size >= 8) {
        Exiv2::byte buf2[8];
        double d;
        memcpy(&d, Data, sizeof(d));
        Exiv2::d2Data(buf2, d, byteOrder);
    }

    // Test getULongLong
    if (Size >= 8) {
        uint64_t val4 = Exiv2::getULongLong(Data, byteOrder);
        (void)val4;
    }

    // Test ull2Data
    if (Size >= 8) {
        Exiv2::byte buf3[8];
        uint64_t val5 = Exiv2::getULongLong(Data, byteOrder);
        Exiv2::ull2Data(buf3, val5, byteOrder);
    }

    return 0;
}