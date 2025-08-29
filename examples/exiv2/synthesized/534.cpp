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
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_534(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf(Size);
    std::memcpy(buf.data(), Data, Size);

    // Test c_data()
    try {
        const Exiv2::byte* c_data_ptr = buf.c_data();
        if (Size > 0 && c_data_ptr == nullptr) return -1;
        
        if (Size > 1) {
            size_t offset = Data[0] % Size;
            c_data_ptr = buf.c_data(offset);
            if (offset < Size && c_data_ptr == nullptr) return -1;
        }
    } catch (...) {
        // Handle exceptions
    }

    // Test data()
    if (Size > 0) {
        Exiv2::byte* data_ptr = buf.data();
        if (data_ptr == nullptr) return -1;

        if (Size > 1) {
            size_t offset = Data[0] % Size;
            data_ptr = buf.data(offset);
            if (data_ptr == nullptr) return -1;
        }
    }

    // Test c_str()
    if (Size > 0) {
        const char* c_str_ptr = buf.c_str();
        if (c_str_ptr == nullptr) return -1;

        if (Size > 1) {
            size_t offset = Data[0] % Size;
            c_str_ptr = buf.c_str(offset);
            if (c_str_ptr == nullptr) return -1;
        }
    }

    // Test size()
    size_t buf_size = buf.size();
    if (buf_size != Size) return -1;

    // Test makeSlice()
    if (Size > 2) {
        size_t begin = Data[0] % Size;
        size_t end = Data[1] % Size;
        if (begin > end) std::swap(begin, end);
        try {
            auto slice = Exiv2::makeSlice(buf, begin, end);
            if (slice.size() != (end - begin)) return -1;
        } catch (...) {
            // Handle exceptions
        }
    }

    // Test ull2Data()
    if (Size >= 8) {
        uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
        Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
        Exiv2::byte output[8];
        size_t bytes_written = Exiv2::ull2Data(output, value, byteOrder);
        if (bytes_written != 8) return -1;
    }

    return 0;
}