// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::s2Data at types.cpp:378:8 in types.hpp
// Exiv2::toData at value.hpp:1412:15 in value.hpp
// Exiv2::ul2Data at types.cpp:342:8 in types.hpp
// Exiv2::d2Data at types.cpp:422:8 in types.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    Exiv2::byte buf[16];
    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);

    // l2Data
    int32_t l;
    std::memcpy(&l, Data + 1, sizeof(l));
    Exiv2::l2Data(buf, l, byteOrder);

    // s2Data
    int16_t s;
    std::memcpy(&s, Data + 5, sizeof(s));
    Exiv2::s2Data(buf, s, byteOrder);

    // toData (specialization for int16_t)
    Exiv2::toData(buf, s, byteOrder);

    // ul2Data
    uint32_t ul;
    std::memcpy(&ul, Data + 7, sizeof(ul));
    Exiv2::ul2Data(buf, ul, byteOrder);

    // d2Data
    double d;
    if (Size >= 19) {
        std::memcpy(&d, Data + 11, sizeof(d));
        Exiv2::d2Data(buf, d, byteOrder);
    }

    // getULongLong
    if (Size >= 8) {
        Exiv2::getULongLong(buf, byteOrder);
    }

    return 0;
}