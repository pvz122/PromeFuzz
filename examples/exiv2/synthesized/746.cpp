// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::XmpArrayValue::toRational at value.cpp:621:25 in value.hpp
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
#include <cstdlib>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_746(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    // Initialize with some default values
    uint32_t n = *reinterpret_cast<const uint32_t*>(Data);
    Data += sizeof(uint32_t);
    Size -= sizeof(uint32_t);

    try {
        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational
        {
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val(std::make_pair(0, 0));
            if (Size >= 2 * sizeof(unsigned int)) {
                unsigned int first = *reinterpret_cast<const unsigned int*>(Data);
                unsigned int second = *reinterpret_cast<const unsigned int*>(Data + sizeof(unsigned int));
                val = Exiv2::ValueType<std::pair<unsigned int, unsigned int>>(std::make_pair(first, second));
                val.toRational(n);
            }
        }

        // Test Exiv2::ValueType<double>::toRational
        {
            Exiv2::ValueType<double> val(0.0);
            if (Size >= sizeof(double)) {
                double d = *reinterpret_cast<const double*>(Data);
                val = Exiv2::ValueType<double>(d);
                val.toRational(n);
            }
        }

        // Test Exiv2::XmpArrayValue::toRational
        {
            Exiv2::XmpArrayValue val(Exiv2::xmpBag);
            val.toRational(n);
        }

        // Test Exiv2::ValueType<float>::toRational
        {
            Exiv2::ValueType<float> val(0.0f);
            if (Size >= sizeof(float)) {
                float f = *reinterpret_cast<const float*>(Data);
                val = Exiv2::ValueType<float>(f);
                val.toRational(n);
            }
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toRational
        {
            Exiv2::ValueType<std::pair<int, int>> val(std::make_pair(0, 0));
            if (Size >= 2 * sizeof(int)) {
                int first = *reinterpret_cast<const int*>(Data);
                int second = *reinterpret_cast<const int*>(Data + sizeof(int));
                val = Exiv2::ValueType<std::pair<int, int>>(std::make_pair(first, second));
                val.toRational(n);
            }
        }
    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}