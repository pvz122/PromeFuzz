// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::focalLength at easyaccess.cpp:473:26 in easyaccess.hpp
// Exiv2::apertureValue at easyaccess.cpp:395:26 in easyaccess.hpp
// Exiv2::fNumber at easyaccess.cpp:379:26 in easyaccess.hpp
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_644(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy ExifData
        Exiv2::ExifData ed;

        // Create keys using single string constructor
        Exiv2::ExifKey key1("Exif.Photo.FocalLength");
        Exiv2::ExifKey key2("Exif.Photo.ApertureValue");
        Exiv2::ExifKey key3("Exif.Photo.FNumber");
        
        Exiv2::Exifdatum datum1(key1);
        Exiv2::Exifdatum datum2(key2);
        Exiv2::Exifdatum datum3(key3);
        
        // Set string values
        std::string val_str(Data, Data + (Size > 100 ? 100 : Size));
        datum1.setValue(val_str);
        datum2.setValue(val_str);
        datum3.setValue(val_str);

        ed.add(datum1);
        ed.add(datum2);
        ed.add(datum3);

        // Test the target functions
        Exiv2::focalLength(ed);
        Exiv2::apertureValue(ed);
        Exiv2::fNumber(ed);

        // Test findKey with a random key
        uint16_t tag = static_cast<uint16_t>(Data[0] % 0xFFFF);
        Exiv2::ExifKey randomKey(tag, "Exif");
        ed.findKey(randomKey);

        // Test iterators
        for (auto it = ed.begin(); it != ed.end(); ++it) {
            // Just iterate through
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}