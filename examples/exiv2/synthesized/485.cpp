// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::subjectDistance at easyaccess.cpp:432:26 in easyaccess.hpp
// Exiv2::lensName at easyaccess.cpp:272:26 in easyaccess.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_485(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy file with the fuzzed data
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        // Read the dummy file into ExifData
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == 0) return 0;
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();

        // Test subjectDistance
        Exiv2::subjectDistance(exifData);

        // Test lensName
        Exiv2::lensName(exifData);

        // Test findKey with a random key
        uint16_t tag = static_cast<uint16_t>(Data[0]);
        std::string groupName = "Exif";
        Exiv2::ExifKey key(tag, groupName);
        exifData.findKey(key);

        // Test begin and end iterators
        for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != exifData.end(); ++it) {
            // Just iterate through the data
        }

        // Test sensingMethod
        Exiv2::sensingMethod(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}