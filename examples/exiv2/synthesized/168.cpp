// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::focalLength at easyaccess.cpp:473:26 in easyaccess.hpp
// Exiv2::brightnessValue at easyaccess.cpp:404:26 in easyaccess.hpp
// Exiv2::sceneMode at easyaccess.cpp:212:26 in easyaccess.hpp
// Exiv2::flash at easyaccess.cpp:452:26 in easyaccess.hpp
// Exiv2::exposureTime at easyaccess.cpp:371:26 in easyaccess.hpp
// Exiv2::fNumber at easyaccess.cpp:379:26 in easyaccess.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/easyaccess.hpp>
#include <exiv2/exiv2.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);
        initialized = true;
    }

    if (Size < 1) {
        return 0;
    }

    try {
        // Write input data to a dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Read metadata from the dummy file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) {
            return 0;
        }
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            return 0;
        }

        // Test all target functions
        Exiv2::focalLength(exifData);
        Exiv2::brightnessValue(exifData);
        Exiv2::sceneMode(exifData);
        Exiv2::flash(exifData);
        Exiv2::exposureTime(exifData);
        Exiv2::fNumber(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}