// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::copyExifToXmp at convert.cpp:1324:6 in convert.hpp
// Exiv2::copyXmpToExif at convert.cpp:1338:6 in convert.hpp
// Exiv2::XmpParser::terminate at xmp.cpp:623:17 in xmp_exiv2.hpp
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

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    // Initialize XMP parser
    Exiv2::XmpParser::initialize();

    // Write input data to a dummy file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(Data), Size);
    outfile.close();

    try {
        // Open the image file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;

        image->readMetadata();

        // Get metadata
        Exiv2::ExifData &exifData = image->exifData();
        Exiv2::XmpData &xmpData = image->xmpData();

        // Copy metadata between formats
        Exiv2::copyExifToXmp(exifData, xmpData);
        Exiv2::copyXmpToExif(xmpData, exifData);

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    // Cleanup
    Exiv2::XmpParser::terminate();
    remove("./dummy_file");

    return 0;
}