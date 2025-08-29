// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::DataValue::copy at value.cpp:124:19 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_193(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize variables from fuzzer input
    int32_t l = *reinterpret_cast<const int32_t*>(Data);
    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
    size_t bufSize = Size > 16 ? 16 : Size;
    Exiv2::byte buf[16];
    memcpy(buf, Data, bufSize);

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test ValueType functions
    try {
        Exiv2::DataValue value(buf, bufSize, byteOrder);
        value.copy(buf, byteOrder);
        value.setDataArea(buf, bufSize);
        value.read(buf, bufSize, byteOrder);

        Exiv2::ValueType<int32_t> valueType(l);
        valueType.copy(buf, byteOrder);
        valueType.setDataArea(buf, bufSize);
        valueType.read(buf, bufSize, byteOrder);

        // Test toData
        Exiv2::toData(buf, l, byteOrder);
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}