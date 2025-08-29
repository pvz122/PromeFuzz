// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
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
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_532(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize ValueType with supported template type
        Exiv2::ValueType<Exiv2::Rational> valueType;

        // Test size() and sizeDataArea() overloads
        size_t valSize = valueType.size();
        size_t valDataAreaSize = valueType.sizeDataArea();

        // Test setDataArea with fuzz data
        if (Size > 0) {
            valueType.setDataArea(Data, Size);
        }

        // Test copy with different byte orders
        if (valSize > 0) {
            Exiv2::byte* buf = new Exiv2::byte[valSize];
            valueType.copy(buf, Exiv2::littleEndian);
            valueType.copy(buf, Exiv2::bigEndian);
            delete[] buf;
        }

        // Test with another supported template type
        Exiv2::ValueType<Exiv2::URational> uRationalValueType;
        uRationalValueType.size();
        uRationalValueType.sizeDataArea();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}