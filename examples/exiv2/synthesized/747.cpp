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

extern "C" int LLVMFuzzerTestOneInput_747(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(unsigned int)) {
        return 0;
    }

    try {
        // Create a ValueType with a pair of unsigned integers
        unsigned int first = 0;
        unsigned int second = 0;
        if (Size >= sizeof(first)) {
            memcpy(&first, Data, sizeof(first));
        }
        if (Size >= sizeof(first) + sizeof(second)) {
            memcpy(&second, Data + sizeof(first), sizeof(second));
        }
        std::pair<unsigned int, unsigned int> pair_data(first, second);
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> value(pair_data);

        // Call size()
        value.size();

        // Call toRational()
        value.toRational();

        // Call count()
        value.count();

        // Call toUint32()
        if (value.count() > 0) {
            value.toUint32();
        }

        // Call toInt64()
        if (value.count() > 0) {
            value.toInt64();
        }

        // Call toString()
        if (value.count() > 0) {
            value.toString(0);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}