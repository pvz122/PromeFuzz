// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1087:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_700(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(uint32_t)) {
        return 0;
    }

    try {
        // Test ValueType<std::pair<unsigned int, unsigned int>>
        {
            uint32_t first = 0;
            uint32_t second = 0;
            if (Size >= 2 * sizeof(uint32_t)) {
                first = *reinterpret_cast<const uint32_t*>(Data);
                second = *reinterpret_cast<const uint32_t*>(Data + sizeof(uint32_t));
            }
            
            std::pair<unsigned int, unsigned int> pair(first, second);
            
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(pair);
            
            // Test size()
            valueType.size();
            
            // Test toRational()
            if (valueType.count() > 0) {
                valueType.toRational(0);
            }
            
            // Test count()
            valueType.count();
            const Exiv2::Value& baseValue = valueType;
            baseValue.count();
            
            // Test toUint32()
            if (valueType.count() > 0) {
                valueType.toUint32(0);
            }
        }

        // Test generic ValueType<uint32_t>
        {
            uint32_t value = 0;
            if (Size >= sizeof(uint32_t)) {
                value = *reinterpret_cast<const uint32_t*>(Data);
            }
            
            Exiv2::ValueType<uint32_t> valueType(value);
            
            // Test size()
            valueType.size();
            
            // Test toRational()
            if (valueType.count() > 0) {
                valueType.toRational(0);
            }
            
            // Test count()
            valueType.count();
            const Exiv2::Value& baseValue = valueType;
            baseValue.count();
            
            // Test toUint32()
            if (valueType.count() > 0) {
                valueType.toUint32(0);
            }
        }
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}