// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_282(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return 0;

    // Initialize buffer and variables
    Exiv2::byte buf[16];
    int32_t l;
    memcpy(&l, Data, sizeof(int32_t));
    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test toData
    Exiv2::toData(buf, l, byteOrder);

    // Test DataValue
    Exiv2::DataValue dataValue;
    if (Size > sizeof(int32_t)) {
        dataValue.read(Data + sizeof(int32_t), Size - sizeof(int32_t), byteOrder);
    }

    // Test ValueType
    Exiv2::ValueType<int32_t> valueType(l);
    valueType.copy(buf, byteOrder);
    if (Size > sizeof(int32_t)) {
        valueType.setDataArea(Data + sizeof(int32_t), Size - sizeof(int32_t));
    }

    std::string str(reinterpret_cast<const char*>(Data), std::min(Size, (size_t)128));
    valueType.read(str);

    return 0;
}