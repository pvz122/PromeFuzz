// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_222(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize buffer and variables
    Exiv2::byte buf[16];
    int32_t l = *reinterpret_cast<const int32_t*>(Data);
    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test DataValue functions
    Exiv2::DataValue dataValue;

    // Test toData
    Exiv2::toData(buf, l, byteOrder);

    // Test DataValue::read
    dataValue.read(Data, Size % 16, byteOrder);

    return 0;
}