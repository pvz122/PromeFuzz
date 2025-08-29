// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::XmpTextValue::toRational at value.cpp:570:24 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_638(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(uint32_t)) {
        return 0;
    }

    try {
        // Test ValueType<std::pair<unsigned int, unsigned int>>::toRational
        {
            uint32_t num, den;
            if (Size >= 2 * sizeof(uint32_t)) {
                memcpy(&num, Data, sizeof(uint32_t));
                memcpy(&den, Data + sizeof(uint32_t), sizeof(uint32_t));
                Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val(std::make_pair(num, den));
                val.toRational();
            }
        }

        // Test ValueType<double>::toRational
        {
            double d;
            if (Size >= sizeof(double)) {
                memcpy(&d, Data, sizeof(double));
                Exiv2::ValueType<double> val(d);
                val.toRational();
            }
        }

        // Test XmpTextValue::toRational
        {
            Exiv2::XmpTextValue val;
            val.toRational();
        }

        // Test ValueType<float>::toRational
        {
            float f;
            if (Size >= sizeof(float)) {
                memcpy(&f, Data, sizeof(float));
                Exiv2::ValueType<float> val(f);
                val.toRational();
            }
        }

        // Test ValueType<std::pair<int, int>>::toRational
        {
            int32_t num, den;
            if (Size >= 2 * sizeof(int32_t)) {
                memcpy(&num, Data, sizeof(int32_t));
                memcpy(&den, Data + sizeof(int32_t), sizeof(int32_t));
                Exiv2::ValueType<std::pair<int, int>> val(std::make_pair(num, den));
                val.toRational();
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}