// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::sharpness at easyaccess.cpp:306:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::contrast at easyaccess.cpp:318:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::macroMode at easyaccess.cpp:231:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
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

extern "C" int LLVMFuzzerTestOneInput_692(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream file("./dummy_file", std::ios::binary);
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();

    try {
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;

        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();

        // Test sharpness
        Exiv2::ExifData::const_iterator sharpnessIt = Exiv2::sharpness(exifData);
        if (sharpnessIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test contrast
        Exiv2::ExifData::const_iterator contrastIt = Exiv2::contrast(exifData);
        if (contrastIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test macroMode
        Exiv2::ExifData::const_iterator macroModeIt = Exiv2::macroMode(exifData);
        if (macroModeIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test findKey
        Exiv2::ExifKey key("Exif.Image.ImageDescription");
        Exiv2::ExifData::const_iterator findKeyIt = exifData.findKey(key);
        if (findKeyIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test begin and end iterators
        for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != exifData.end(); ++it) {
            // Do nothing, just ensure iteration doesn't crash
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}