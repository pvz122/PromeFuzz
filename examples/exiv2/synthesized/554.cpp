// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
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
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_554(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize variables
    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    int32_t l = static_cast<int32_t>(Size);
    Exiv2::byte buf[4];

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test ValueType functions
    try {
        Exiv2::DataValue dataValue;
        Exiv2::ValueType<int32_t> valueType;

        // Test copy
        valueType.copy(buf, byteOrder);

        // Test setDataArea
        if (Size > 4) {
            dataValue.setDataArea(Data, Size % 128); // Limit size to prevent excessive memory usage
        }

        // Test read (string)
        std::string str(reinterpret_cast<const char*>(Data), Size);
        valueType.read(str);

        // Test toData
        Exiv2::toData(buf, l, byteOrder);

        // Test DataValue::read
        if (Size > 8) {
            dataValue.read(Data, Size % 64, byteOrder); // Limit size to prevent excessive memory usage
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}