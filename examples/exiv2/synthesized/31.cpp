// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::ExifData::clear at exif.cpp:470:16 in exif.hpp
// Exiv2::ExifParser::decode at exif.cpp:490:23 in exif.hpp
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
#include <exiv2/exif.hpp>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create DataBuf from input
        Exiv2::DataBuf buf(Data, Size);

        // Call c_data with offset 0 (default)
        const Exiv2::byte* data_ptr = buf.c_data();
        (void)data_ptr; // Avoid unused variable warning

        // Call size
        size_t buf_size = buf.size();
        (void)buf_size; // Avoid unused variable warning

        // Create ExifData and clear it
        Exiv2::ExifData exifData;
        exifData.clear();

        // Call ExifParser::decode
        if (Size > 0) {
            Exiv2::ExifParser::decode(exifData, Data, Size);
        }
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}