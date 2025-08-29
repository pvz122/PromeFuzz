// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::LangAltValue::toRational at value.cpp:736:24 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_218(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) {
        return 0;
    }

    size_t n = *reinterpret_cast<const size_t*>(Data);
    Data += sizeof(size_t);
    Size -= sizeof(size_t);

    // ValueType<std::pair<unsigned int, unsigned int>>::toRational
    {
        std::pair<unsigned int, unsigned int> pair(0, 0);
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(pair);
        try {
            (void)valueType.toRational(n);
        } catch (...) {
        }
    }

    // ValueType<double>::toRational
    {
        double val = 0.0;
        Exiv2::ValueType<double> valueType(val);
        try {
            (void)valueType.toRational(n);
        } catch (...) {
        }
    }

    // LangAltValue::toRational
    {
        Exiv2::LangAltValue langAltValue;
        try {
            (void)langAltValue.toRational(n);
        } catch (...) {
        }
    }

    // ValueType<float>::toRational
    {
        float val = 0.0f;
        Exiv2::ValueType<float> valueType(val);
        try {
            (void)valueType.toRational(n);
        } catch (...) {
        }
    }

    // ValueType<std::pair<int, int>>::toRational
    {
        std::pair<int, int> pair(0, 0);
        Exiv2::ValueType<std::pair<int, int>> valueType(pair);
        try {
            (void)valueType.toRational(n);
        } catch (...) {
        }
    }

    return 0;
}