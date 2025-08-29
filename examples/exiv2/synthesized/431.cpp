// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::XmpTextValue::count at value.cpp:522:22 in value.hpp
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
#include <exiv2/exiv2.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/asfvideo.hpp>
#include <exiv2/exif.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_431(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::ExifThumbC::writeFile
    {
        Exiv2::ExifData exifData;
        Exiv2::ExifThumbC thumb(exifData);
        thumb.writeFile("./dummy_file");
    }

    // Test Exiv2::XmpTextValue::count
    {
        Exiv2::XmpTextValue textValue;
        (void)textValue.count();
    }

    // Test Exiv2::DataBuf::size
    {
        Exiv2::DataBuf buf(Data, Size % 1024);
        (void)buf.size();
    }

    return 0;
}