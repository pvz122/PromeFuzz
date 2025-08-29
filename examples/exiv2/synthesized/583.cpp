// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
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
#include <exiv2/exiv2.hpp>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_583(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test with unsignedShort type
        Exiv2::UShortValue ushortVal;
        std::string dataStr(reinterpret_cast<const char*>(Data), Size);
        ushortVal.read(dataStr);
        ushortVal.size();
        ushortVal.toRational();
        ushortVal.count();
        ushortVal.toUint32();
        ushortVal.toInt64();
        ushortVal.toString(0);

        // Test with unsignedLong type
        Exiv2::ULongValue ulongVal;
        ulongVal.read(dataStr);
        ulongVal.size();
        ulongVal.toRational();
        ulongVal.count();
        ulongVal.toUint32();
        ulongVal.toInt64();
        ulongVal.toString(0);

        // Test with Rational type
        Exiv2::URationalValue rationalVal;
        rationalVal.read(dataStr);
        rationalVal.size();
        rationalVal.toRational();
        rationalVal.count();
        rationalVal.toUint32();
        rationalVal.toInt64();
        rationalVal.toString(0);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}