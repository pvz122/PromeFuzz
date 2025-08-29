// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::read at value.cpp:110:16 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_744(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize variables
    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    int32_t l = static_cast<int32_t>(Size);
    Exiv2::byte buf[16] = {0};
    std::string str(reinterpret_cast<const char*>(Data), Size);

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test ValueType functions
    Exiv2::ValueType<int32_t> valueType;
    valueType.copy(buf, byteOrder);
    valueType.setDataArea(Data, Size % 16);
    valueType.read(str);

    // Test toData
    Exiv2::toData(buf, l, byteOrder);

    // Test DataValue functions
    Exiv2::DataValue dataValue(Data, Size % 16, byteOrder);
    dataValue.read(Data, Size % 16, byteOrder);
    dataValue.read(str);

    return 0;
}