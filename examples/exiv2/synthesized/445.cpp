// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_445(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create ValueType instances with compatible types
        Exiv2::ValueType<uint16_t> ushortVal(static_cast<uint16_t>(Data[0]), Exiv2::unsignedShort);
        Exiv2::ValueType<uint32_t> ulongVal(static_cast<uint32_t>(Data[0]), Exiv2::unsignedLong);
        
        // Test with basic types that won't cause conversion errors
        Exiv2::ValueType<int16_t> shortVal(static_cast<int16_t>(Data[0]), Exiv2::signedShort);
        Exiv2::ValueType<int32_t> longVal(static_cast<int32_t>(Data[0]), Exiv2::signedLong);

        // Test copy function with different byte orders
        Exiv2::byte buf[128];
        ushortVal.copy(buf, Exiv2::littleEndian);
        ulongVal.copy(buf, Exiv2::bigEndian);
        shortVal.copy(buf, Exiv2::littleEndian);
        longVal.copy(buf, Exiv2::bigEndian);

        // Test size function
        ushortVal.size();
        ulongVal.size();
        shortVal.size();
        longVal.size();

        // Test setDataArea function
        if (Size > 1) {
            ushortVal.setDataArea(Data, Size % 128);
            ulongVal.setDataArea(Data, Size % 128);
            shortVal.setDataArea(Data, Size % 128);
            longVal.setDataArea(Data, Size % 128);
        }

        // Test sizeDataArea function
        ushortVal.sizeDataArea();
        ulongVal.sizeDataArea();
        shortVal.sizeDataArea();
        longVal.sizeDataArea();

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}