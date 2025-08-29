// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Exifdatum::key at exif.cpp:272:24 in exif.hpp
// Exiv2::Exifdatum::tag at exif.cpp:296:21 in exif.hpp
// Exiv2::Exifdatum::count at exif.cpp:328:19 in exif.hpp
// Exiv2::Exifdatum::value at exif.cpp:198:25 in exif.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exif.hpp>
#include <exiv2/error.hpp>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        // Create dummy ExifKey
        Exiv2::ExifKey key("Exif.Image.Make");
        Exiv2::Exifdatum datum(key);

        // Call Exifdatum functions
        (void)datum.key();
        (void)datum.tag();
        (void)datum.count();
        try {
            (void)datum.value();
        } catch (const Exiv2::Error&) {}

        // Create ExifData and populate with some data
        Exiv2::ExifData exifData;
        exifData.add(datum);

        // Call ExifData functions in specified order
        auto it1 = exifData.findKey(key);
        auto end1 = exifData.end();
        if (it1 != end1) exifData.erase(it1);

        auto it2 = exifData.findKey(key);
        auto end2 = exifData.end();
        if (it2 != end2) exifData.erase(it2);

        auto it3 = exifData.findKey(key);
        auto end3 = exifData.end();
        if (it3 != end3) exifData.erase(it3);

        auto it4 = exifData.findKey(key);
        auto end4 = exifData.end();
        if (it4 != end4) exifData.erase(it4);

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    return 0;
}