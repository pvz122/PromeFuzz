// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::resize at types.cpp:100:15 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::makeSlice at types.cpp:198:14 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
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
#include <vector>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_448(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf;
    if (Size > 0) {
        buf.resize(Size);
        memcpy(buf.data(), Data, Size);
    }

    // Test c_data()
    try {
        size_t offset = Size > 1 ? Data[0] % Size : 0;
        const Exiv2::byte* c_data_ptr = buf.c_data(offset);
        (void)c_data_ptr; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test data()
    try {
        size_t offset = Size > 1 ? Data[0] % Size : 0;
        Exiv2::byte* data_ptr = buf.data(offset);
        (void)data_ptr; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test c_str()
    try {
        size_t offset = Size > 1 ? Data[0] % Size : 0;
        const char* c_str_ptr = buf.c_str(offset);
        (void)c_str_ptr; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test size()
    size_t buf_size = buf.size();
    (void)buf_size; // Avoid unused variable warning

    // Test makeSlice()
    try {
        size_t begin = Size > 1 ? Data[0] % Size : 0;
        size_t end = Size > 2 ? Data[1] % Size : Size;
        if (begin > end) std::swap(begin, end);
        auto slice = Exiv2::makeSlice(buf, begin, end);
        (void)slice; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test ull2Data()
    try {
        if (Size >= 8) {
            Exiv2::byte output[8];
            uint64_t value = *reinterpret_cast<const uint64_t*>(Data);
            Exiv2::ByteOrder order = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
            size_t bytes_written = Exiv2::ull2Data(output, value, order);
            (void)bytes_written; // Avoid unused variable warning
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}