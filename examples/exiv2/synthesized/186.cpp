// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ur2Data at types.cpp:372:8 in types.hpp
// Exiv2::toData at value.hpp:1404:15 in value.hpp
// Exiv2::ul2Data at types.cpp:342:8 in types.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::append at image.cpp:921:6 in image.hpp
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
#include <exiv2/image.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_186(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    Exiv2::byte buf[8];
    uint32_t ulValue;
    uint64_t ullValue;
    Exiv2::URational urValue;

    // Initialize values from fuzzer input
    std::memcpy(&ulValue, Data, sizeof(ulValue));
    std::memcpy(&ullValue, Data, sizeof(ullValue));
    std::memcpy(&urValue, Data, sizeof(urValue));

    // Test ur2Data
    Exiv2::ur2Data(buf, urValue, byteOrder);

    // Test toData<URational>
    Exiv2::toData<Exiv2::URational>(buf, urValue, byteOrder);

    // Test ul2Data
    Exiv2::ul2Data(buf, ulValue, byteOrder);

    // Test getULongLong
    Exiv2::getULongLong(buf, byteOrder);

    // Test append
    Exiv2::Blob blob;
    Exiv2::append(blob, buf, sizeof(buf));

    // Test ull2Data
    Exiv2::ull2Data(buf, ullValue, byteOrder);

    return 0;
}