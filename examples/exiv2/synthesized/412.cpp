// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_412(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize buffer and variables
    Exiv2::byte buf[16];
    Exiv2::ByteOrder byteOrder = (data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
    int32_t l = static_cast<int32_t>(size);
    std::string str(reinterpret_cast<const char*>(data), size);

    // Test l2Data
    Exiv2::l2Data(buf, l, byteOrder);

    // Test DataValue functions
    try {
        Exiv2::DataValue dataValue(data, size, byteOrder);
        dataValue.read(data, size, byteOrder);
    } catch (...) {
        // Ignore exceptions
    }

    // Test toData specialization
    Exiv2::toData(buf, l, byteOrder);

    return 0;
}