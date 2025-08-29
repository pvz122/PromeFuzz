// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::XmpTextValue::count at value.cpp:522:22 in value.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_407(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // Test Exiv2::ExifThumbC::writeFile
        {
            Exiv2::ExifData exifData;
            Exiv2::ExifThumbC thumb(exifData);
            thumb.writeFile("./dummy_file");
        }

        // Test Exiv2::XmpTextValue::count
        {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::XmpTextValue value(str);
            (void)value.count();
        }

        // Test Exiv2::DataBuf::size
        {
            Exiv2::DataBuf buf(Size);
            if (Size > 0) {
                std::memcpy(buf.data(), Data, Size);
            }
            (void)buf.size();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}