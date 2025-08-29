// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::toUint32 at value.cpp:726:24 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toUint32 at value.hpp:1606:38 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType<float>::toUint32 at value.hpp:1597:35 in value.hpp
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
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_454(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz Exiv2::LangAltValue::toUint32
    try {
        std::string buf(reinterpret_cast<const char*>(Data), Size);
        Exiv2::LangAltValue langAltValue(buf);
        langAltValue.toUint32(Size % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<double>::toUint32
    try {
        Exiv2::ValueType<double> doubleValue;
        std::string doubleBuf(reinterpret_cast<const char*>(Data), Size);
        doubleValue.read(doubleBuf);
        doubleValue.toUint32(Size % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32
    try {
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> pairUintValue;
        std::string pairUintBuf(reinterpret_cast<const char*>(Data), Size);
        pairUintValue.read(pairUintBuf);
        pairUintValue.toUint32(Size % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<std::pair<int, int>>::toUint32
    try {
        Exiv2::ValueType<std::pair<int, int>> pairIntValue;
        std::string pairIntBuf(reinterpret_cast<const char*>(Data), Size);
        pairIntValue.read(pairIntBuf);
        pairIntValue.toUint32(Size % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<float>::toUint32
    try {
        Exiv2::ValueType<float> floatValue;
        std::string floatBuf(reinterpret_cast<const char*>(Data), Size);
        floatValue.read(floatBuf);
        floatValue.toUint32(Size % 10);
    } catch (...) {}

    return 0;
}