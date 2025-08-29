// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::DataValue::copy at value.cpp:124:19 in value.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
#include <iostream>
#include <cstring>
#include <cstdint>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_687(const uint8_t *data, size_t size) {
    if (size < 4) return 0;

    // Initialize variables from fuzz input
    int32_t l = *reinterpret_cast<const int32_t*>(data);
    Exiv2::ByteOrder byteOrder = size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    size_t bufSize = size > 8 ? 8 : size;
    Exiv2::byte buf[8];
    memcpy(buf, data, bufSize);

    // Test l2Data
    Exiv2::byte output[4];
    Exiv2::l2Data(output, l, byteOrder);

    // Test DataValue functions
    Exiv2::DataValue dataValue;

    // Test copy
    Exiv2::byte copyBuf[128];
    dataValue.copy(copyBuf, byteOrder);

    // Test toData
    Exiv2::toData(buf, l, byteOrder);

    return 0;
}