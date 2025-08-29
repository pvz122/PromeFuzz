// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64 at value.hpp:1611:38 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_332(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(unsigned int)) {
        return 0;
    }

    try {
        // Create a ValueType with a pair of unsigned integers
        unsigned int first, second;
        memcpy(&first, Data, sizeof(unsigned int));
        memcpy(&second, Data + sizeof(unsigned int), sizeof(unsigned int));
        std::pair<unsigned int, unsigned int> pairData(first, second);
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(pairData);

        // Call size()
        valueType.size();

        // Call toRational()
        valueType.toRational();

        // Call count()
        valueType.count();

        // Call toUint32()
        valueType.toUint32();

        // Call toInt64()
        valueType.toInt64();

        // Call toString()
        valueType.toString(0);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}