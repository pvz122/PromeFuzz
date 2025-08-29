// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::DateValue::toUint32 at value.cpp:863:21 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_645(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Fuzz Exiv2::DateValue::toUint32
    try {
        Exiv2::DateValue dateValue;
        (void)dateValue.toUint32(Data[0] % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<double>::toUint32
    try {
        Exiv2::ValueType<double> doubleValue;
        (void)doubleValue.toUint32(Data[0] % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32
    try {
        unsigned int first = Size > 0 ? Data[0] : 0;
        unsigned int second = Size > 1 ? Data[1] : 0;
        std::pair<unsigned int, unsigned int> uintPair = {first, second};
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairValue(uintPair);
        (void)uintPairValue.toUint32(Data[0] % 2);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<std::pair<int, int>>::toUint32
    try {
        int first = Size > 0 ? static_cast<int>(Data[0]) : 0;
        int second = Size > 1 ? static_cast<int>(Data[1]) : 0;
        std::pair<int, int> intPair = {first, second};
        Exiv2::ValueType<std::pair<int, int>> intPairValue(intPair);
        (void)intPairValue.toUint32(Data[0] % 2);
    } catch (...) {}

    // Fuzz Exiv2::ValueType::toUint32 (generic case)
    try {
        Exiv2::ValueType<int> genericValue;
        (void)genericValue.toUint32(Data[0] % 10);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<float>::toUint32
    try {
        Exiv2::ValueType<float> floatValue;
        (void)floatValue.toUint32(Data[0] % 10);
    } catch (...) {}

    return 0;
}