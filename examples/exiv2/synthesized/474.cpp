// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::makeSlice at types.cpp:198:14 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
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

extern "C" int LLVMFuzzerTestOneInput_474(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create DataBuf from input
        Exiv2::DataBuf buf(Data, Size);

        // Test c_data()
        if (buf.size() > 0) {
            const Exiv2::byte* c_data_ptr = buf.c_data();
            if (Size > 1) {
                size_t offset = Data[0] % buf.size();
                c_data_ptr = buf.c_data(offset);
            }
        }

        // Test data()
        if (buf.size() > 0) {
            Exiv2::byte* data_ptr = buf.data();
            if (Size > 1) {
                size_t offset = Data[0] % buf.size();
                data_ptr = buf.data(offset);
            }
        }

        // Test c_str()
        if (buf.size() > 0) {
            const char* c_str_ptr = buf.c_str();
            if (Size > 1) {
                size_t offset = Data[0] % buf.size();
                c_str_ptr = buf.c_str(offset);
            }
        }

        // Test size()
        size_t buf_size = buf.size();

        // Test makeSlice()
        if (buf.size() > 1) {
            size_t begin = Data[0] % buf.size();
            size_t end = begin + (Data[1] % (buf.size() - begin));
            auto slice = Exiv2::makeSlice(buf, begin, end);
        }

        // Test ull2Data()
        if (Size > sizeof(uint64_t)) {
            uint64_t value;
            std::memcpy(&value, Data, sizeof(uint64_t));
            Exiv2::byte output[8];
            Exiv2::ull2Data(output, value, Exiv2::littleEndian);
            Exiv2::ull2Data(output, value, Exiv2::bigEndian);
        }
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}