// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_460(const uint8_t *data, size_t size) {
    if (size < 8) return 0;

    // Initialize variables from fuzzer input
    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(data[0] % 3);
    int32_t l;
    memcpy(&l, data + 1, sizeof(int32_t));
    size_t bufSize = size - 5;
    if (bufSize < 4) return 0;
    const Exiv2::byte* buf = data + 5;

    // Test l2Data
    Exiv2::byte outputBuf[4];
    Exiv2::l2Data(outputBuf, l, byteOrder);

    // Test ValueType functions
    try {
        Exiv2::ValueType<int32_t> valueType(l, Exiv2::signedLong);
        Exiv2::byte copyBuf[16];
        valueType.copy(copyBuf, byteOrder);
        valueType.read(buf, bufSize, byteOrder);
        valueType.setDataArea(buf, bufSize);
    } catch (...) {
        // Ignore exceptions
    }

    // Test toData
    Exiv2::toData(outputBuf, l, byteOrder);

    // Test DataValue functions
    try {
        Exiv2::DataValue dataValue(buf, bufSize, byteOrder);
        dataValue.read(buf, bufSize, byteOrder);
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}