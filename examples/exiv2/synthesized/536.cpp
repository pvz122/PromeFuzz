// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::makeSlice at types.cpp:198:14 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_536(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf(Size);
    if (Size > 0) {
        std::memcpy(buf.data(), Data, Size);
    }

    // Test c_data()
    try {
        const Exiv2::byte* c_data_ptr = buf.c_data();
        if (Size > 1) {
            size_t offset = Data[0] % Size;
            c_data_ptr = buf.c_data(offset);
        }
    } catch (...) {
        // Ignore exceptions
    }

    // Test data()
    if (Size > 0) {
        Exiv2::byte* data_ptr = buf.data();
        if (Size > 1) {
            size_t offset = Data[0] % Size;
            data_ptr = buf.data(offset);
        }
    }

    // Test c_str()
    if (Size > 0) {
        const char* c_str_ptr = buf.c_str();
        if (Size > 1) {
            size_t offset = Data[0] % Size;
            c_str_ptr = buf.c_str(offset);
        }
    }

    // Test size()
    size_t buf_size = buf.size();

    // Test makeSlice()
    if (Size > 2) {
        size_t begin = Data[0] % Size;
        size_t end = Data[1] % Size;
        if (begin > end) std::swap(begin, end);
        try {
            auto slice = Exiv2::makeSlice(buf, begin, end);
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test ull2Data()
    if (Size >= 8) {
        uint64_t value;
        std::memcpy(&value, Data, sizeof(value));
        Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
        Exiv2::byte output[8];
        Exiv2::ull2Data(output, value, byteOrder);
    }

    return 0;
}