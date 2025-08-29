// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ur2Data at types.cpp:372:8 in types.hpp
// Exiv2::toData at value.hpp:1428:15 in value.hpp
// Exiv2::us2Data at types.cpp:331:8 in types.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
    Exiv2::byte buf[16];

    // Test ur2Data
    Exiv2::URational ur(static_cast<uint32_t>(Data[1]), static_cast<uint32_t>(Data[2]));
    Exiv2::ur2Data(buf, ur, byteOrder);

    // Test toData (Rational specialization)
    Exiv2::Rational r(static_cast<int32_t>(Data[3]), static_cast<int32_t>(Data[4]));
    Exiv2::toData<Exiv2::Rational>(buf, r, byteOrder);

    // Test us2Data
    uint16_t us = static_cast<uint16_t>(Data[5] << 8 | Data[6]);
    Exiv2::us2Data(buf, us, byteOrder);

    // Test getULongLong
    uint64_t ull = Exiv2::getULongLong(Data + 7, byteOrder);

    // Test r2Data
    Exiv2::r2Data(buf, r, byteOrder);

    // Test ull2Data
    Exiv2::ull2Data(buf, ull, byteOrder);

    return 0;
}