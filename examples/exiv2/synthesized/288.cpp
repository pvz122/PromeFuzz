// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::XmpArrayValue::toUint32 at value.cpp:613:25 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_288(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::XmpArrayValue::toUint32
        {
            Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
            uint32_t val = xmpArrayValue.toUint32(Data[0] % 10);
        }

        // Test Exiv2::ValueType<double>::toUint32
        {
            double d = static_cast<double>(Data[0]);
            Exiv2::ValueType<double> valueType(reinterpret_cast<const Exiv2::byte*>(&d), sizeof(d), Exiv2::littleEndian);
            uint32_t val = valueType.toUint32(Data[0] % 10);
        }

        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32
        {
            std::pair<unsigned int, unsigned int> pair = {Data[0], Data[1]};
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(
                reinterpret_cast<const Exiv2::byte*>(&pair), sizeof(pair), Exiv2::littleEndian);
            uint32_t val = valueType.toUint32(Data[0] % 10);
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toUint32
        {
            std::pair<int, int> pair = {static_cast<int>(Data[0]), static_cast<int>(Data[1])};
            Exiv2::ValueType<std::pair<int, int>> valueType(
                reinterpret_cast<const Exiv2::byte*>(&pair), sizeof(pair), Exiv2::littleEndian);
            uint32_t val = valueType.toUint32(Data[0] % 10);
        }

        // Test Exiv2::ValueType<float>::toUint32
        {
            float f = static_cast<float>(Data[0]);
            Exiv2::ValueType<float> valueType(reinterpret_cast<const Exiv2::byte*>(&f), sizeof(f), Exiv2::littleEndian);
            uint32_t val = valueType.toUint32(Data[0] % 10);
        }
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}