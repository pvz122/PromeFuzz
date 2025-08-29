// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_166(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    try {
        // Create dummy data
        std::pair<unsigned int, unsigned int> pair;
        if (Size >= sizeof(pair)) {
            memcpy(&pair, Data, sizeof(pair));
        } else {
            pair = {0, 0};
        }

        // Create ValueType instance
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(pair);

        // Test size()
        valueType.size();

        // Test toRational()
        if (valueType.count() > 0) {
            valueType.toRational(0);
        }

        // Test count()
        valueType.count();
        static_cast<const Exiv2::ValueType<std::pair<unsigned int, unsigned int>>&>(valueType).count();

        // Test toUint32() variants
        if (valueType.count() > 0) {
            valueType.toUint32(0);
            static_cast<const Exiv2::ValueType<std::pair<unsigned int, unsigned int>>&>(valueType).toUint32(0);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}