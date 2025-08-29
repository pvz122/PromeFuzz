// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:453:16 in exif.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:453:16 in exif.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::ExifData::sortByKey at exif.cpp:474:16 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:462:36 in exif.hpp
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
#include <exiv2/exif.hpp>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_269(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        Exiv2::ExifData exifData;

        // Create some dummy Exif data
        Exiv2::ExifKey key1("Exif.Image.Make");
        std::unique_ptr<Exiv2::Value> value1(Exiv2::Value::create(Exiv2::asciiString));
        value1->read("TestMake");
        exifData.add(key1, value1.get());

        Exiv2::ExifKey key2("Exif.Image.Model");
        std::unique_ptr<Exiv2::Value> value2(Exiv2::Value::create(Exiv2::asciiString));
        value2->read("TestModel");
        exifData.add(key2, value2.get());

        // Test erase
        if (!exifData.empty()) {
            auto it = exifData.begin();
            exifData.erase(it);
        }

        // Test sortByKey
        exifData.sortByKey();

        // Test findKey (both overloads)
        Exiv2::ExifKey findKey("Exif.Image.Make");
        const Exiv2::ExifData& constExifData = exifData;
        auto it1 = exifData.findKey(findKey);
        auto it2 = constExifData.findKey(findKey);

        // Test begin/end
        for (auto it = exifData.begin(); it != exifData.end(); ++it) {
            // Just iterate
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}