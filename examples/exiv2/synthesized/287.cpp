// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_287(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize buffer and variables
    Exiv2::byte buf[16];
    int32_t l = *reinterpret_cast<const int32_t*>(Data);
    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test toData
    Exiv2::toData<int32_t>(buf, l, byteOrder);

    // Create DataValue object
    Exiv2::DataValue dataValue(Data, Size % 16, byteOrder);

    // Test DataValue::read
    dataValue.read(Data, Size % 16, byteOrder);

    // Create ValueType object with explicit type
    Exiv2::ValueType<int32_t> valueType(Data, Size % 16, byteOrder, Exiv2::signedLong);

    // Test ValueType::copy
    valueType.copy(buf, byteOrder);

    // Test ValueType::setDataArea
    valueType.setDataArea(Data, Size % 16);

    // Test ValueType::read
    std::string str(reinterpret_cast<const char*>(Data), Size % 128);
    valueType.read(str);

    return 0;
}