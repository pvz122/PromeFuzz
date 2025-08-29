// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
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
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_730(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test ValueType<unsigned int>
        Exiv2::ValueType<unsigned int> uintVal(static_cast<unsigned int>(Data[0]));
        uintVal.size();
        uintVal.toRational();
        uintVal.count();

        // Test ValueType<std::pair<unsigned int, unsigned int>>
        std::pair<unsigned int, unsigned int> pairVal = {static_cast<unsigned int>(Data[0]), static_cast<unsigned int>(Data[1 % Size])};
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> pairType(pairVal);
        pairType.size();
        pairType.toRational();
        pairType.count();
        if (pairType.count() > 0) {
            pairType.toUint32(0);
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}