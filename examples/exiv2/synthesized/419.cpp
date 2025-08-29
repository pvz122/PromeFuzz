// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::getUShort at types.cpp:246:10 in types.hpp
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::toData at value.hpp:1388:15 in value.hpp
// Exiv2::getValue at value.hpp:1330:17 in value.hpp
// Exiv2::us2Data at types.cpp:331:8 in types.hpp
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
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_419(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    Exiv2::byte buf[10];
    memcpy(buf, Data, 10);

    // Test getValue<uint16_t>
    try {
        Exiv2::getValue<uint16_t>(buf, byteOrder);
    } catch (...) {}

    // Test getUShort with array
    try {
        Exiv2::getUShort(buf, byteOrder);
    } catch (...) {}

    // Test toData<uint16_t>
    try {
        uint16_t val = Exiv2::getValue<uint16_t>(buf, byteOrder);
        Exiv2::toData(buf, val, byteOrder);
    } catch (...) {}

    // Test us2Data
    try {
        uint16_t val = Exiv2::getValue<uint16_t>(buf, byteOrder);
        Exiv2::us2Data(buf, val, byteOrder);
    } catch (...) {}

    // Test getULongLong
    try {
        Exiv2::getULongLong(buf, byteOrder);
    } catch (...) {}

    // Test ull2Data
    try {
        uint64_t val = Exiv2::getULongLong(buf, byteOrder);
        Exiv2::ull2Data(buf, val, byteOrder);
    } catch (...) {}

    return 0;
}