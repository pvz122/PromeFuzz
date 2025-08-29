// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::resize at types.cpp:100:15 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::read_uint8 at types.cpp:108:25 in types.hpp
// Exiv2::DataBuf::alloc at types.cpp:96:15 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_364(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataBuf with random size (modulo to avoid too large allocations)
    size_t buf_size = Size % 1024 + 1;
    Exiv2::DataBuf buf(buf_size);

    // Fill buffer with fuzzer data (truncated if needed)
    size_t copy_size = Size > buf_size ? buf_size : Size;
    std::memcpy(buf.data(), Data, copy_size);

    // Test c_data() with random offset
    try {
        size_t offset1 = Size % (buf_size + 1);
        const Exiv2::byte* cptr = buf.c_data(offset1);
        (void)cptr; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test data() with random offset
    try {
        size_t offset2 = Size % (buf_size + 1);
        Exiv2::byte* ptr = buf.data(offset2);
        (void)ptr; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test resize()
    try {
        size_t new_size = Size % 2048;
        buf.resize(new_size);
    } catch (...) {
        // Ignore exceptions
    }

    // Test read_uint8()
    try {
        size_t offset3 = Size % (buf.size() + 1);
        uint8_t val = buf.read_uint8(offset3);
        (void)val; // Avoid unused variable warning
    } catch (...) {
        // Ignore exceptions
    }

    // Test alloc()
    try {
        size_t alloc_size = Size % 2048;
        buf.alloc(alloc_size);
    } catch (...) {
        // Ignore exceptions
    }

    // Test size()
    (void)buf.size();

    return 0;
}