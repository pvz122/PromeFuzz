// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
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
#include <exiv2/types.hpp>
#include <cstdint>
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_552(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    try {
        // Test ValueType::size()
        Exiv2::ValueType<uint32_t> valueType1;
        (void)valueType1.size();

        // Test ValueType::toRational()
        Exiv2::ValueType<Exiv2::Rational> valueType2;
        (void)valueType2.toRational();

        // Test ValueType::count() overloads
        Exiv2::ValueType<uint32_t> valueType3;
        (void)valueType3.count();

        // Test ValueType<std::pair<unsigned int, unsigned int>>::toUint32()
        std::vector<std::pair<unsigned int, unsigned int>> pairs;
        if (Size >= 2 * sizeof(uint32_t)) {
            uint32_t first, second;
            memcpy(&first, Data, sizeof(uint32_t));
            memcpy(&second, Data + sizeof(uint32_t), sizeof(uint32_t));
            pairs.emplace_back(first, second);
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType4(pairs[0]);
            (void)valueType4.toUint32(0);
        }

        // Test ValueType::toUint32()
        Exiv2::ValueType<uint32_t> valueType5;
        (void)valueType5.toUint32();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}