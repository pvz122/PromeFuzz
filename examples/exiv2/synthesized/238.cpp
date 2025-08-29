// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_238(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    try {
        // Create a dummy ValueType object (using uint16_t as template type)
        Exiv2::ValueType<uint16_t> valueType;

        // Use first byte to determine byte order
        Exiv2::ByteOrder byteOrder = (data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

        // Call size() functions
        (void)valueType.size();
        (void)valueType.ValueType<uint16_t>::size();

        // Call sizeDataArea() functions
        (void)valueType.sizeDataArea();
        (void)valueType.ValueType<uint16_t>::sizeDataArea();

        // Prepare buffer for copy operation
        if (size > 1) {
            Exiv2::byte* buf = new Exiv2::byte[size-1];
            size_t copied = valueType.copy(buf, byteOrder);
            delete[] buf;
        }

        // Call setDataArea if we have enough data
        if (size > 2) {
            valueType.setDataArea(data + 1, size - 1);
        }

        // Test copy constructor
        Exiv2::ValueType<uint16_t> copyConstructed(valueType);

    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}