// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::brightnessValue at easyaccess.cpp:404:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::focalLength at easyaccess.cpp:473:26 in easyaccess.hpp
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
#include <cstring>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_548(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (!outFile) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Read the dummy file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (!image) return 0;
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) return 0;

        // Test brightnessValue
        Exiv2::ExifData::const_iterator brightnessIt = Exiv2::brightnessValue(exifData);
        if (brightnessIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test focalLength
        Exiv2::ExifData::const_iterator focalLengthIt = Exiv2::focalLength(exifData);
        if (focalLengthIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test macroMode
        Exiv2::ExifData::const_iterator macroModeIt = Exiv2::macroMode(exifData);
        if (macroModeIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test findKey with a random key
        uint16_t tag = static_cast<uint16_t>(Data[0] << 8 | Data[1 % Size]);
        std::string groupName = "Exif";
        Exiv2::ExifKey key(tag, groupName);
        Exiv2::ExifData::const_iterator findKeyIt = exifData.findKey(key);
        if (findKeyIt != exifData.end()) {
            // Do nothing, just ensure it doesn't crash
        }

        // Test iterators
        for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != exifData.end(); ++it) {
            // Do nothing, just ensure iteration doesn't crash
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}