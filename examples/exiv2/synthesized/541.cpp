// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::DataValue::copy at value.cpp:124:19 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_541(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize variables
    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    int32_t l = static_cast<int32_t>(Size);
    Exiv2::byte buf[16] = {0};
    const Exiv2::byte* dataBuf = reinterpret_cast<const Exiv2::byte*>(Data);

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test DataValue functions
    Exiv2::DataValue dataValue(dataBuf, Size % 16, byteOrder);
    dataValue.copy(buf, byteOrder);

    // Test toData
    Exiv2::toData(buf, l, byteOrder);

    return 0;
}