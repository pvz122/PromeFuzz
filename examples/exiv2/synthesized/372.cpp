// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::focalLength at easyaccess.cpp:473:26 in easyaccess.hpp
// Exiv2::contrast at easyaccess.cpp:318:26 in easyaccess.hpp
// Exiv2::exposureTime at easyaccess.cpp:371:26 in easyaccess.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_372(const uint8_t *Data, size_t Size) {
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

        // Test focalLength
        Exiv2::focalLength(exifData);

        // Test contrast
        Exiv2::contrast(exifData);

        // Test exposureTime
        Exiv2::exposureTime(exifData);

        // Test findKey with a sample key
        Exiv2::ExifKey key("Exif.Photo.FNumber");
        exifData.findKey(key);

        // Test begin and end iterators
        for (Exiv2::ExifData::const_iterator it = exifData.begin(); it != exifData.end(); ++it) {
            // Just iterate through the metadata
        }

    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}