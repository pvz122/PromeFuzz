// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::DateValue::toRational at value.cpp:876:21 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_759(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t) * 2) return 0;

    // Create ValueType<std::pair<unsigned int, unsigned int>>
    uint32_t u1 = 0, u2 = 0;
    if (Size >= sizeof(uint32_t) * 2) {
        memcpy(&u1, Data, sizeof(uint32_t));
        memcpy(&u2, Data + sizeof(uint32_t), sizeof(uint32_t));
    }
    Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val1(std::make_pair(u1, u2));
    try { val1.toRational(); } catch (...) {}

    // Create ValueType<double>
    double d = 0.0;
    if (Size >= sizeof(uint32_t) * 2 + sizeof(double)) {
        memcpy(&d, Data + sizeof(uint32_t) * 2, sizeof(double));
    }
    Exiv2::ValueType<double> val2(d);
    try { val2.toRational(); } catch (...) {}

    // Create ValueType<float>
    float f = 0.0f;
    if (Size >= sizeof(uint32_t) * 2 + sizeof(double) + sizeof(float)) {
        memcpy(&f, Data + sizeof(uint32_t) * 2 + sizeof(double), sizeof(float));
    }
    Exiv2::ValueType<float> val3(f);
    try { val3.toRational(); } catch (...) {}

    // Create ValueType<std::pair<int, int>>
    int32_t i1 = 0, i2 = 0;
    if (Size >= sizeof(int32_t) * 2) {
        memcpy(&i1, Data, sizeof(int32_t));
        memcpy(&i2, Data + sizeof(int32_t), sizeof(int32_t));
    }
    Exiv2::ValueType<std::pair<int, int>> val4(std::make_pair(i1, i2));
    try { val4.toRational(); } catch (...) {}

    // Create DateValue
    int32_t year = 0, month = 0, day = 0;
    if (Size >= sizeof(int32_t) * 3) {
        memcpy(&year, Data, sizeof(int32_t));
        memcpy(&month, Data + sizeof(int32_t), sizeof(int32_t));
        memcpy(&day, Data + sizeof(int32_t) * 2, sizeof(int32_t));
    }
    Exiv2::DateValue dateVal(year, month, day);
    try { dateVal.toRational(); } catch (...) {}

    return 0;
}