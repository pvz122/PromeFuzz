// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1340:18 in value.hpp
// Exiv2::getRational at types.cpp:290:10 in types.hpp
// Exiv2::getUShort at types.cpp:246:10 in types.hpp
// Exiv2::getDouble at types.cpp:308:8 in types.hpp
// Exiv2::getShort at types.cpp:276:9 in types.hpp
// Exiv2::getURational at types.cpp:270:11 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_148(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    Exiv2::ByteOrder orders[] = {Exiv2::littleEndian, Exiv2::bigEndian};
    const Exiv2::byte* buf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test getValue<URational>
    try {
        Exiv2::getValue<Exiv2::URational>(buf, orders[Size % 2]);
    } catch (...) {}

    // Test getRational
    try {
        Exiv2::getRational(buf, orders[Size % 2]);
    } catch (...) {}

    // Test getUShort
    try {
        Exiv2::getUShort(buf, orders[Size % 2]);
    } catch (...) {}

    // Test getDouble
    try {
        Exiv2::getDouble(buf, orders[Size % 2]);
    } catch (...) {}

    // Test getShort
    try {
        Exiv2::getShort(buf, orders[Size % 2]);
    } catch (...) {}

    // Test getURational
    try {
        Exiv2::getURational(buf, orders[Size % 2]);
    } catch (...) {}

    return 0;
}