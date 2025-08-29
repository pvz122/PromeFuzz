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
#include <cstdint>
#include <cstring>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

extern "C" int LLVMFuzzerTestOneInput_256(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
    uint16_t ushort_val = 0;
    uint64_t ulonglong_val = 0;
    Exiv2::byte buf[8];

    // Test getValue<uint16_t>
    if (Size >= 2) {
        ushort_val = Exiv2::getValue<uint16_t>(Data, byteOrder);
    }

    // Test getUShort
    if (Size >= 2) {
        ushort_val = Exiv2::getUShort(Data, byteOrder);
    }

    // Test toData<uint16_t>
    if (Size >= 2) {
        Exiv2::toData(buf, ushort_val, byteOrder);
    }

    // Test us2Data
    if (Size >= 2) {
        Exiv2::us2Data(buf, ushort_val, byteOrder);
    }

    // Test getULongLong
    if (Size >= 8) {
        ulonglong_val = Exiv2::getULongLong(Data, byteOrder);
    }

    // Test ull2Data
    if (Size >= 8) {
        Exiv2::ull2Data(buf, ulonglong_val, byteOrder);
    }

    return 0;
}