// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_650(const uint8_t *data, size_t size) {
    if (size < 2) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf(size);
    memcpy(buf.data(), data, std::min(size, buf.size()));

    // Test c_data()
    try {
        size_t offset = data[0] % (size + 1); // Ensure offset is within bounds
        const Exiv2::byte* c_data_ptr = buf.c_data(offset);
        (void)c_data_ptr; // Avoid unused variable warning
    } catch (...) {
        // Handle exceptions
    }

    // Test data()
    if (size > 0) {
        size_t offset = data[0] % size; // Ensure offset is within bounds
        Exiv2::byte* data_ptr = buf.data(offset);
        (void)data_ptr; // Avoid unused variable warning
    }

    // Test c_str()
    if (size > 0) {
        size_t offset = data[0] % size; // Ensure offset is within bounds
        const char* c_str_ptr = buf.c_str(offset);
        (void)c_str_ptr; // Avoid unused variable warning
    }

    // Test size()
    size_t buf_size = buf.size();
    (void)buf_size; // Avoid unused variable warning

    // Test makeSlice()
    try {
        size_t begin = data[0] % (size + 1);
        size_t end = begin;
        if (size - begin > 0) {
            end = begin + (data[1] % (size - begin));
        }
        auto slice = Exiv2::makeSlice(buf, begin, end);
        (void)slice; // Avoid unused variable warning
    } catch (...) {
        // Handle exceptions
    }

    // Test ull2Data()
    if (size >= 8) {
        Exiv2::ByteOrder byteOrder = (data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
        uint64_t value = *reinterpret_cast<const uint64_t*>(data);
        Exiv2::byte output[8];
        size_t bytes_written = Exiv2::ull2Data(output, value, byteOrder);
        (void)bytes_written; // Avoid unused variable warning
    }

    return 0;
}