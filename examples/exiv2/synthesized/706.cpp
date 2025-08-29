// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::DateValue::toRational at value.cpp:876:21 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_706(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;

    // Initialize values with fuzzed data
    int n = *reinterpret_cast<const int*>(Data);
    Data += sizeof(int);
    Size -= sizeof(int);

    // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational
    {
        if (Size >= 2 * sizeof(unsigned int)) {
            unsigned int first = *reinterpret_cast<const unsigned int*>(Data);
            Data += sizeof(unsigned int);
            unsigned int second = *reinterpret_cast<const unsigned int*>(Data);
            Data += sizeof(unsigned int);
            Size -= 2 * sizeof(unsigned int);

            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val(std::make_pair(first, second));
            try {
                val.toRational(n);
            } catch (...) {}
        }
    }

    // Test Exiv2::ValueType::toRational (base case)
    {
        Exiv2::ValueType<int> val(0);
        try {
            val.toRational(n);
        } catch (...) {}
    }

    // Test Exiv2::DateValue::toRational
    {
        Exiv2::DateValue dateVal;
        try {
            dateVal.toRational(n);
        } catch (...) {}
    }

    // Test Exiv2::ValueType<double>::toRational
    {
        if (Size >= sizeof(double)) {
            double d = *reinterpret_cast<const double*>(Data);
            Data += sizeof(double);
            Size -= sizeof(double);

            Exiv2::ValueType<double> val(d);
            try {
                val.toRational(n);
            } catch (...) {}
        }
    }

    // Test Exiv2::ValueType<float>::toRational
    {
        if (Size >= sizeof(float)) {
            float f = *reinterpret_cast<const float*>(Data);
            Data += sizeof(float);
            Size -= sizeof(float);

            Exiv2::ValueType<float> val(f);
            try {
                val.toRational(n);
            } catch (...) {}
        }
    }

    // Test Exiv2::ValueType<std::pair<int, int>>::toRational
    {
        if (Size >= 2 * sizeof(int)) {
            int first = *reinterpret_cast<const int*>(Data);
            Data += sizeof(int);
            int second = *reinterpret_cast<const int*>(Data);
            Data += sizeof(int);
            Size -= 2 * sizeof(int);

            Exiv2::ValueType<std::pair<int, int>> val(std::make_pair(first, second));
            try {
                val.toRational(n);
            } catch (...) {}
        }
    }

    return 0;
}