// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::lightSource at easyaccess.cpp:444:26 in easyaccess.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::apertureValue at easyaccess.cpp:395:26 in easyaccess.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
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
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_527(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::ExifData exifData;

        // Create a dummy ExifKey
        Exiv2::ExifKey key("Exif.Photo.UserComment");
        Exiv2::Exifdatum datum(key);
        std::string value(reinterpret_cast<const char*>(Data), Size);
        datum.setValue(value);
        exifData.add(datum);

        // Test lightSource
        Exiv2::lightSource(exifData);

        // Test findKey
        exifData.findKey(key);

        // Test apertureValue
        Exiv2::apertureValue(exifData);

        // Test begin and end
        for (auto it = exifData.begin(); it != exifData.end(); ++it) {
            // Just iterate
        }

        // Test make
        Exiv2::make(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}