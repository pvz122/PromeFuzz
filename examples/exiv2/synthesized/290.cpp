// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1350:16 in value.hpp
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::getLong at types.cpp:283:9 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_290(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test getValue<int32_t>
    if (Size >= 4) {
        try {
            Exiv2::getValue<int32_t>(buf, byteOrder);
        } catch (...) {}
    }

    // Test l2Data
    if (Size >= 4) {
        Exiv2::byte outBuf[4];
        int32_t val = *reinterpret_cast<const int32_t*>(Data);
        Exiv2::l2Data(outBuf, val, byteOrder);
    }

    // Test toData<int32_t>
    if (Size >= 4) {
        Exiv2::byte outBuf[4];
        int32_t val = *reinterpret_cast<const int32_t*>(Data);
        Exiv2::toData(outBuf, val, byteOrder);
    }

    // Test getLong
    if (Size >= 4) {
        Exiv2::getLong(buf, byteOrder);
    }

    // Test getULongLong
    if (Size >= 8) {
        Exiv2::getULongLong(buf, byteOrder);
    }

    // Test ull2Data
    if (Size >= 8) {
        Exiv2::byte outBuf[8];
        uint64_t val = *reinterpret_cast<const uint64_t*>(Data);
        Exiv2::ull2Data(outBuf, val, byteOrder);
    }

    return 0;
}