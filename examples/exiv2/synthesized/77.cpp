// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64 at value.hpp:1611:38 in value.hpp
// Exiv2::TimeValue::toInt64 at value.cpp:1034:20 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toInt64 at value.hpp:1602:37 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::XmpValue::read at value.cpp:463:15 in value.hpp
// Exiv2::XmpArrayValue::toInt64 at value.cpp:609:24 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Fuzz Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64
    try {
        unsigned int first = Size > 0 ? Data[0] : 0;
        unsigned int second = Size > 1 ? Data[1] : 0;
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val(std::make_pair(first, second));
        val.toInt64(Size > 2 ? Data[2] % 2 : 0);
    } catch (...) {}

    // Fuzz Exiv2::TimeValue::toInt64
    try {
        int32_t hour = Size > 0 ? Data[0] % 24 : 0;
        int32_t minute = Size > 1 ? Data[1] % 60 : 0;
        int32_t second = Size > 2 ? Data[2] % 60 : 0;
        int32_t tzHour = Size > 3 ? Data[3] % 12 : 0;
        int32_t tzMinute = Size > 4 ? Data[4] % 60 : 0;
        Exiv2::TimeValue time(hour, minute, second, tzHour, tzMinute);
        time.toInt64();
    } catch (...) {}

    // Fuzz Exiv2::ValueType<std::pair<int, int>>::toInt64
    try {
        int first = Size > 0 ? static_cast<int>(Data[0]) : 0;
        int second = Size > 1 ? static_cast<int>(Data[1]) : 0;
        Exiv2::ValueType<std::pair<int, int>> val(std::make_pair(first, second));
        val.toInt64(Size > 2 ? Data[2] % 2 : 0);
    } catch (...) {}

    // Fuzz Exiv2::ValueType<float>::toInt64
    try {
        float value = Size > 0 ? static_cast<float>(Data[0]) : 0.0f;
        Exiv2::ValueType<float> val(value);
        val.toInt64();
    } catch (...) {}

    // Fuzz Exiv2::ValueType::toInt64 (generic case)
    try {
        int value = Size > 0 ? static_cast<int>(Data[0]) : 0;
        Exiv2::ValueType<int> val(value);
        val.toInt64();
    } catch (...) {}

    // Fuzz Exiv2::XmpArrayValue::toInt64
    try {
        Exiv2::XmpArrayValue xmpVal(Exiv2::xmpBag);
        if (Size > 1) {
            xmpVal.read(Data, Size, Exiv2::littleEndian);
            xmpVal.toInt64(Size > 2 ? Data[2] % 2 : 0);
        }
    } catch (...) {}

    return 0;
}