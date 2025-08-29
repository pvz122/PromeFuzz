// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::sharpness at easyaccess.cpp:306:26 in easyaccess.hpp
// Exiv2::contrast at easyaccess.cpp:318:26 in easyaccess.hpp
// Exiv2::lensName at easyaccess.cpp:272:26 in easyaccess.hpp
// Exiv2::exposureBiasValue at easyaccess.cpp:414:26 in easyaccess.hpp
// Exiv2::subjectArea at easyaccess.cpp:483:26 in easyaccess.hpp
// Exiv2::make at easyaccess.cpp:349:26 in easyaccess.hpp
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
#include <exiv2/easyaccess.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
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
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == 0) {
            return 0;
        }
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            return 0;
        }

        Exiv2::sharpness(exifData);
        Exiv2::contrast(exifData);
        Exiv2::lensName(exifData);
        Exiv2::exposureBiasValue(exifData);
        Exiv2::subjectArea(exifData);
        Exiv2::make(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}