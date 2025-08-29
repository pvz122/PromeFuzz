// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::toUint32 at value.cpp:726:24 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toUint32 at value.hpp:1606:38 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_615(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz Exiv2::LangAltValue::toUint32
    {
        Exiv2::LangAltValue langAltValue;
        langAltValue.toUint32(0);
    }

    // Fuzz Exiv2::ValueType<double>::toUint32
    {
        Exiv2::ValueType<double> doubleValue;
        doubleValue.value_.push_back(0.0);
        doubleValue.toUint32(0);
    }

    // Fuzz Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32
    {
        std::pair<unsigned int, unsigned int> uintPair = {0, 0};
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairValue;
        uintPairValue.value_.push_back(uintPair);
        uintPairValue.toUint32(0);
    }

    // Fuzz Exiv2::ValueType<std::pair<int, int>>::toUint32
    {
        std::pair<int, int> intPair = {0, 0};
        Exiv2::ValueType<std::pair<int, int>> intPairValue;
        intPairValue.value_.push_back(intPair);
        intPairValue.toUint32(0);
    }

    // Fuzz Exiv2::ValueType::toUint32 (generic)
    {
        Exiv2::ValueType<int> genericValue;
        genericValue.value_.push_back(0);
        genericValue.toUint32(0);
    }

    // Fuzz Exiv2::ValueType<float>::toUint32
    {
        Exiv2::ValueType<float> floatValue;
        floatValue.value_.push_back(0.0f);
        floatValue.toUint32(0);
    }

    return 0;
}