// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_694(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize ValueType object with uint32_t type
        Exiv2::ValueType<uint32_t> valueType;

        // Test size() function (both overloads)
        size_t size1 = valueType.size();
        size_t size2 = valueType.sizeDataArea();

        // Test setDataArea() function
        if (Size > 0) {
            valueType.setDataArea(Data, Size);
        }

        // Test sizeDataArea() function (both overloads)
        size_t dataAreaSize1 = valueType.sizeDataArea();
        size_t dataAreaSize2 = valueType.sizeDataArea();

        // Test copy() function with different byte orders
        if (Size > 0) {
            Exiv2::byte* buf = new Exiv2::byte[Size];
            size_t copied1 = valueType.copy(buf, Exiv2::littleEndian);
            size_t copied2 = valueType.copy(buf, Exiv2::bigEndian);
            delete[] buf;
        }

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}