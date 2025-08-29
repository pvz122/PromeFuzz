// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::sizeDataArea at value.hpp:1674:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_396(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    try {
        // Create ValueType instance with int type
        Exiv2::ValueType<int> valueType;

        // Test size() overloads
        valueType.size();
        static_cast<Exiv2::ValueType<int>*>(&valueType)->size();

        // Test sizeDataArea() overloads
        valueType.sizeDataArea();
        static_cast<Exiv2::ValueType<int>*>(&valueType)->sizeDataArea();

        // Test setDataArea with fuzz data
        if (size > 0) {
            valueType.setDataArea(data, size);
        }

        // Test copy with different byte orders
        if (size > 0) {
            uint8_t* buf = new uint8_t[size];
            valueType.copy(buf, Exiv2::littleEndian);
            valueType.copy(buf, Exiv2::bigEndian);
            delete[] buf;
        }

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}