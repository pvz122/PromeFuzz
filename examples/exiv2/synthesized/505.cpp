// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64 at value.hpp:1611:38 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_505(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create ValueType instances with different types
        Exiv2::ValueType<unsigned int> uintVal(static_cast<unsigned int>(Data[0]));
        Exiv2::ValueType<int> intVal(static_cast<int>(Data[0]));
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> pairVal(
            std::make_pair(static_cast<unsigned int>(Data[0]), static_cast<unsigned int>(Data[0 % Size])));

        // Test size() function
        uintVal.size();
        intVal.size();
        pairVal.size();

        // Test toRational() function
        if (Size > 1) {
            uintVal.toRational(Data[1] % 2);
            intVal.toRational(Data[1] % 2);
            pairVal.toRational(Data[1] % 2);
        }

        // Test count() function
        uintVal.count();
        intVal.count();
        pairVal.count();

        // Test toUint32() function
        if (Size > 2) {
            pairVal.toUint32(Data[2] % 2);
        }

        // Test toInt64() function
        if (Size > 3) {
            uintVal.toInt64(Data[3] % 2);
            intVal.toInt64(Data[3] % 2);
            pairVal.toInt64(Data[3] % 2);
        }

        // Test toString() function
        if (Size > 4) {
            uintVal.toString(Data[4] % 2);
            intVal.toString(Data[4] % 2);
            pairVal.toString(Data[4] % 2);
        }

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}