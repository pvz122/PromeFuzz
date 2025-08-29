// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::LangAltValue::toUint32 at value.cpp:726:24 in value.hpp
// Exiv2::DateValue::toUint32 at value.cpp:863:21 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
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
#include <exiv2/exiv2.hpp>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_213(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Fuzz Exiv2::LangAltValue::toUint32
        {
            Exiv2::LangAltValue langAltValue;
            langAltValue.toUint32(static_cast<size_t>(Data[0] % 10));
        }

        // Fuzz Exiv2::DateValue::toUint32
        {
            Exiv2::DateValue dateValue;
            dateValue.toUint32(static_cast<size_t>(Data[0] % 10));
        }

        // Fuzz Exiv2::ValueType<double>::toUint32
        {
            double d = static_cast<double>(Data[0]);
            Exiv2::ValueType<double> doubleValue(d);
            doubleValue.toUint32(static_cast<size_t>(Data[0] % 10));
        }

        // Fuzz Exiv2::ValueType<std::pair<int, int>>::toUint32
        {
            std::pair<int, int> pair = {static_cast<int>(Data[0]), static_cast<int>(Data[0])};
            Exiv2::ValueType<std::pair<int, int>> pairValue(pair);
            pairValue.toUint32(static_cast<size_t>(Data[0] % 10));
        }

        // Fuzz Exiv2::ValueType<float>::toUint32
        {
            float f = static_cast<float>(Data[0]);
            Exiv2::ValueType<float> floatValue(f);
            floatValue.toUint32(static_cast<size_t>(Data[0] % 10));
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}