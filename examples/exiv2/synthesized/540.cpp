// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::makeSlice at types.cpp:198:14 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_540(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint64_t)) return 0;

    // Initialize DataBuf with fuzzer input
    Exiv2::DataBuf buf(Size);
    if (Size > 0) {
        std::memcpy(buf.data(), Data, Size);
    }

    // Test c_data()
    try {
        if (Size > 0) {
            buf.c_data(Size / 2);
        }
    } catch (...) {}

    // Test data()
    if (Size > 0) {
        buf.data(Size / 2);
    }

    // Test c_str()
    if (Size > 0) {
        buf.c_str(Size / 2);
    }

    // Test size()
    buf.size();

    // Test makeSlice()
    try {
        if (Size >= 2) {
            Exiv2::makeSlice(buf, Size / 4, Size / 2);
        }
    } catch (...) {}

    // Test ull2Data()
    if (Size >= sizeof(uint64_t)) {
        uint64_t value;
        std::memcpy(&value, Data, sizeof(uint64_t));
        if (Size >= sizeof(uint64_t)) {
            Exiv2::ull2Data(buf.data(), value, Exiv2::littleEndian);
            Exiv2::ull2Data(buf.data(), value, Exiv2::bigEndian);
        }
    }

    return 0;
}