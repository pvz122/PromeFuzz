// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_446(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    try {
        // Create test data
        unsigned int u1 = *reinterpret_cast<const unsigned int*>(Data);
        unsigned int u2 = *reinterpret_cast<const unsigned int*>(Data + 4);
        int i1 = *reinterpret_cast<const int*>(Data);
        int i2 = *reinterpret_cast<const int*>(Data + 4);
        float f = *reinterpret_cast<const float*>(Data);
        double d = *reinterpret_cast<const double*>(Data);

        // Test ValueType<std::pair<unsigned int, unsigned int>>::toRational
        {
            std::pair<unsigned int, unsigned int> pair(u1, u2);
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> value(pair);
            value.toRational();
            value.toRational(1);
        }

        // Test ValueType<std::pair<int, int>>::toRational
        {
            std::pair<int, int> pair(i1, i2);
            Exiv2::ValueType<std::pair<int, int>> value(pair);
            value.toRational();
            value.toRational(1);
        }

        // Test ValueType<double>::toRational
        {
            Exiv2::ValueType<double> value(d);
            value.toRational();
            value.toRational(1);
        }

        // Test ValueType<float>::toRational
        {
            Exiv2::ValueType<float> value(f);
            value.toRational();
            value.toRational(1);
        }

        // Test default ValueType::toRational
        {
            Exiv2::ValueType<int> value(i1);
            value.toRational();
            value.toRational(1);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}