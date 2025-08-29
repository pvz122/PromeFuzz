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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_435(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize byte order randomly
    Exiv2::ByteOrder byteOrder = (data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
    const uint8_t* fuzz_data = data + 1;
    size_t fuzz_size = size - 1;

    // Test l2Data
    {
        Exiv2::byte buf[4];
        int32_t val = 0;
        if (fuzz_size >= sizeof(val)) {
            memcpy(&val, fuzz_data, sizeof(val));
            Exiv2::l2Data(buf, val, byteOrder);
        }
    }

    // Test DataValue
    {
        Exiv2::DataValue dataValue;
        if (fuzz_size > 0) {
            dataValue.read(fuzz_data, fuzz_size, byteOrder);
        }
    }

    // Test toData
    {
        Exiv2::byte buf[4];
        int32_t val = 0;
        if (fuzz_size >= sizeof(val)) {
            memcpy(&val, fuzz_data, sizeof(val));
            Exiv2::toData(buf, val, byteOrder);
        }
    }

    return 0;
}