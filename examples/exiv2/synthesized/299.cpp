// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::model at easyaccess.cpp:357:26 in easyaccess.hpp
// Exiv2::lightSource at easyaccess.cpp:444:26 in easyaccess.hpp
// Exiv2::copyXmpToExif at convert.cpp:1338:6 in convert.hpp
// Exiv2::exvGettext at types.cpp:508:13 in types.hpp
// Exiv2::isoSpeed at easyaccess.cpp:66:26 in easyaccess.hpp
// Exiv2::copyExifToXmp at convert.cpp:1324:6 in convert.hpp
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

extern "C" int LLVMFuzzerTestOneInput_299(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Read metadata from file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;
        image->readMetadata();

        // Get Exif and XMP data
        Exiv2::ExifData &exifData = image->exifData();
        Exiv2::XmpData &xmpData = image->xmpData();

        // Test model()
        Exiv2::model(exifData);

        // Test lightSource()
        Exiv2::lightSource(exifData);

        // Test copyXmpToExif()
        Exiv2::copyXmpToExif(xmpData, exifData);

        // Test exvGettext()
        const char* testStr = "Test string";
        Exiv2::exvGettext(testStr);

        // Test isoSpeed()
        Exiv2::isoSpeed(exifData);

        // Test copyExifToXmp()
        Exiv2::copyExifToXmp(exifData, xmpData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}