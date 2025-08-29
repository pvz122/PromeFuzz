// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::write_uint16 at types.cpp:129:22 in types.hpp
// Exiv2::DataBuf::write_uint32 at types.cpp:143:22 in types.hpp
// Exiv2::DataBuf::write_uint64 at types.cpp:157:22 in types.hpp
// Exiv2::DataBuf::read_uint16 at types.cpp:122:26 in types.hpp
// Exiv2::DataBuf::read_uint32 at types.cpp:136:26 in types.hpp
// Exiv2::DataBuf::read_uint64 at types.cpp:150:26 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    // Initialize DataBuf with random data
    Exiv2::DataBuf buf(Data, Size);

    // Extract parameters from input
    size_t offset = *reinterpret_cast<const size_t*>(Data) % (Size - 8);
    uint16_t val16 = *reinterpret_cast<const uint16_t*>(Data + sizeof(size_t));
    uint32_t val32 = *reinterpret_cast<const uint32_t*>(Data + sizeof(size_t) + sizeof(uint16_t));
    uint64_t val64 = *reinterpret_cast<const uint64_t*>(Data + sizeof(size_t) + sizeof(uint16_t) + sizeof(uint32_t));
    Exiv2::ByteOrder order = static_cast<Exiv2::ByteOrder>(Data[Size - 1] % 3);

    try {
        // Test write operations
        buf.write_uint16(offset, val16, order);
        buf.write_uint32(offset, val32, order);
        buf.write_uint64(offset, val64, order);

        // Test read operations
        (void)buf.read_uint16(offset, order);
        (void)buf.read_uint32(offset, order);
        (void)buf.read_uint64(offset, order);
    } catch (const std::out_of_range&) {
        // Expected exception for invalid offsets
    }

    return 0;
}