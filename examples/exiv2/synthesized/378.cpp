// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType::toFloat at value.hpp:1620:21 in value.hpp
// Exiv2::Iptcdatum::toFloat at iptc.cpp:144:18 in iptc.hpp
// Exiv2::StringValueBase::toFloat at value.cpp:219:24 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat at value.hpp:1634:36 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toFloat at value.hpp:1626:35 in value.hpp
// Exiv2::DateValue::toFloat at value.cpp:872:18 in value.hpp
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
#include <exiv2/iptc.hpp>
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_378(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::ValueType::toFloat
    try {
        Exiv2::ValueType<int> intValue(static_cast<int>(Data[0]));
        intValue.toFloat();
    } catch (...) {}

    // Test Exiv2::Iptcdatum::toFloat
    try {
        Exiv2::IptcKey key("Iptc.Application2.Keywords");
        Exiv2::Iptcdatum datum(key);
        datum.toFloat();
    } catch (...) {}

    // Test Exiv2::StringValue::toFloat
    try {
        Exiv2::StringValue stringValue(std::string(reinterpret_cast<const char*>(Data), Size));
        stringValue.toFloat();
    } catch (...) {}

    // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat
    try {
        std::pair<unsigned int, unsigned int> uintPair(static_cast<unsigned int>(Data[0]), static_cast<unsigned int>(Data[1 % Size]));
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairValue(uintPair);
        uintPairValue.toFloat();
    } catch (...) {}

    // Test Exiv2::ValueType<std::pair<int, int>>::toFloat
    try {
        std::pair<int, int> intPair(static_cast<int>(Data[0]), static_cast<int>(Data[1 % Size]));
        Exiv2::ValueType<std::pair<int, int>> intPairValue(intPair);
        intPairValue.toFloat();
    } catch (...) {}

    // Test Exiv2::DateValue::toFloat
    try {
        Exiv2::DateValue dateValue;
        dateValue.toFloat();
    } catch (...) {}

    return 0;
}