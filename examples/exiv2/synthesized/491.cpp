// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64 at value.hpp:1611:38 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
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
#include <cstddef>
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_491(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(unsigned int)) {
        return 0;
    }

    try {
        // Create a ValueType instance with a pair of unsigned integers
        unsigned int first = 0;
        unsigned int second = 0;
        if (Size >= sizeof(first) + sizeof(second)) {
            memcpy(&first, Data, sizeof(first));
            memcpy(&second, Data + sizeof(first), sizeof(second));
        }
        std::pair<unsigned int, unsigned int> pair_data(first, second);
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> value_type(pair_data);

        // Test size()
        value_type.size();

        // Test toRational()
        value_type.toRational();

        // Test count()
        value_type.count();

        // Test toUint32()
        if (value_type.count() > 0) {
            value_type.toUint32(0);
        }

        // Test toInt64()
        if (value_type.count() > 0) {
            value_type.toInt64(0);
        }

        // Test toString()
        if (value_type.count() > 0) {
            value_type.toString(0);
        }

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}