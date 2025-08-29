// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::ExifThumbC::copy at exif.cpp:371:21 in exif.hpp
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
// Exiv2::ExifThumbC::mimeType at exif.cpp:393:25 in exif.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy ExifData
        Exiv2::ExifData exifData;
        Exiv2::ExifThumbC thumb(exifData);

        // Create DataBuf from input
        Exiv2::DataBuf buf(Data, Size);

        // Call functions in specified order
        buf.c_str();
        buf.size();
        Exiv2::DataBuf thumbCopy = thumb.copy();
        thumbCopy.empty();
        thumb.mimeType();
        thumbCopy.size();
        thumb.writeFile("./dummy_file");

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}