// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::Cr2Parser::decode at cr2image.cpp:100:22 in cr2image.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
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
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <iostream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_180(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::DataBuf::c_data
        Exiv2::DataBuf buf1(Size);
        if (Size > 0) {
            std::memcpy(buf1.data(), Data, Size);
            const Exiv2::byte* c_data_ptr = buf1.c_data(Size / 2);
            (void)c_data_ptr; // Avoid unused variable warning
        }

        // Test Exiv2::Cr2Parser::decode
        Exiv2::ExifData exifData;
        Exiv2::IptcData iptcData;
        Exiv2::XmpData xmpData;
        Exiv2::Cr2Parser::decode(exifData, iptcData, xmpData, Data, Size);

        // Test Exiv2::DataBuf::data
        Exiv2::DataBuf buf2(Size);
        if (Size > 0) {
            std::memcpy(buf2.data(), Data, Size);
            Exiv2::byte* data_ptr = buf2.data(Size / 2);
            (void)data_ptr; // Avoid unused variable warning
        }

        // Test Exiv2::DataValue::read
        Exiv2::DataValue dataValue;
        dataValue.read(Data, Size);

        // Test Exiv2::DataBuf::read_uint64
        if (Size >= 8) {
            Exiv2::DataBuf buf3(Size);
            std::memcpy(buf3.data(), Data, Size);
            uint64_t val = buf3.read_uint64(0, Exiv2::littleEndian);
            (void)val; // Avoid unused variable warning
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}