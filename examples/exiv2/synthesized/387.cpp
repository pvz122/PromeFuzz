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
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_387(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) {
        return 0;
    }

    try {
        // Create a ValueType with pair<unsigned int, unsigned int>
        std::pair<unsigned int, unsigned int> pair_data;
        if (Size >= sizeof(pair_data)) {
            memcpy(&pair_data, Data, sizeof(pair_data));
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> value_type(pair_data);

            // Call size()
            value_type.size();

            // Call toRational()
            value_type.toRational();

            // Call count()
            value_type.count();

            // Call toUint32()
            if (value_type.count() > 0) {
                value_type.toUint32();
            }

            // Call toInt64()
            if (value_type.count() > 0) {
                value_type.toInt64();
            }

            // Call toString()
            if (value_type.count() > 0) {
                value_type.toString(0);
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}