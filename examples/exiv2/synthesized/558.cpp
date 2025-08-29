// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::DateValue::toUint32 at value.cpp:863:21 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toUint32 at value.hpp:1606:38 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_558(const uint8_t *Data, size_t Size) {
    if (Size < 12) return 0;

    // Create DateValue
    int32_t year = *reinterpret_cast<const int32_t*>(Data);
    int32_t month = *reinterpret_cast<const int32_t*>(Data + 4);
    int32_t day = *reinterpret_cast<const int32_t*>(Data + 8);
    Exiv2::DateValue dateValue(year, month, day);
    dateValue.toUint32();

    // Create ValueType<double>
    double d = *reinterpret_cast<const double*>(Data);
    Exiv2::ValueType<double> doubleValue(d);
    doubleValue.toUint32();

    // Create ValueType<std::pair<unsigned int, unsigned int>>
    unsigned int u1 = *reinterpret_cast<const unsigned int*>(Data);
    unsigned int u2 = *reinterpret_cast<const unsigned int*>(Data + 4);
    std::pair<unsigned int, unsigned int> uintPair(u1, u2);
    Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairValue(uintPair);
    uintPairValue.toUint32();

    // Create ValueType<std::pair<int, int>>
    int i1 = *reinterpret_cast<const int*>(Data);
    int i2 = *reinterpret_cast<const int*>(Data + 4);
    std::pair<int, int> intPair(i1, i2);
    Exiv2::ValueType<std::pair<int, int>> intPairValue(intPair);
    intPairValue.toUint32();

    // Create ValueType<float>
    float f = *reinterpret_cast<const float*>(Data);
    Exiv2::ValueType<float> floatValue(f);
    floatValue.toUint32();

    return 0;
}