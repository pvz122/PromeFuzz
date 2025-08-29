// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::subjectDistance at easyaccess.cpp:432:26 in easyaccess.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::apertureValue at easyaccess.cpp:395:26 in easyaccess.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::sensingMethod at easyaccess.cpp:507:26 in easyaccess.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_723(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);
        initialized = true;
    }

    try {
        // Write data to a dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Try to read the file with Exiv2
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) return 0;

        // Test subjectDistance
        Exiv2::subjectDistance(exifData);

        // Test findKey with a dummy key
        Exiv2::ExifKey key("Exif.Photo.ExposureTime");
        exifData.findKey(key);

        // Test apertureValue
        Exiv2::apertureValue(exifData);

        // Test begin/end iterators
        for (auto it = exifData.begin(); it != exifData.end(); ++it) {
            // Just iterate through
        }

        // Test sensingMethod
        Exiv2::sensingMethod(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}