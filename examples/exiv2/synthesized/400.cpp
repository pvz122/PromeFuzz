// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_400(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create ValueType instance with uint32_t as template parameter
        Exiv2::ValueType<uint32_t> valueType;

        // Fuzz setDataArea
        if (Size > 0) {
            valueType.setDataArea(Data, Size);
        }

        // Fuzz sizeDataArea (both overloads)
        valueType.sizeDataArea();
        static_cast<const Exiv2::ValueType<uint32_t>&>(valueType).sizeDataArea();

        // Fuzz size (both overloads)
        valueType.size();
        static_cast<const Exiv2::ValueType<uint32_t>&>(valueType).size();

        // Fuzz copy with different byte orders
        if (Size > 0) {
            Exiv2::byte* buf = new Exiv2::byte[Size];
            valueType.copy(buf, Exiv2::littleEndian);
            valueType.copy(buf, Exiv2::bigEndian);
            delete[] buf;
        }

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}