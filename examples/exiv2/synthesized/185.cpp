// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:453:16 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:482:30 in exif.hpp
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_185(const uint8_t *Data, size_t Size) {
    try {
        // Create dummy ExifData
        Exiv2::ExifData exifData;

        // Check if ExifData is empty
        bool isEmpty = exifData.empty();

        // Add some dummy data if empty to test other functions
        if (isEmpty && Size > 0) {
            std::string keyStr(reinterpret_cast<const char*>(Data), Size % 100); // Limit size to avoid too long keys
            try {
                Exiv2::ExifKey key(keyStr);
                Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
                value->read("0");
                exifData.add(key, value.get());
            } catch (...) {
                // Ignore invalid keys
            }
        }

        // Test findKey
        if (Size > 0) {
            std::string keyStr(reinterpret_cast<const char*>(Data), Size % 100);
            try {
                Exiv2::ExifKey key(keyStr);
                auto it = exifData.findKey(key);
            } catch (...) {
                // Ignore invalid keys
            }
        }

        // Test erase functions if ExifData is not empty
        if (!exifData.empty()) {
            // Erase single element
            auto it = exifData.begin();
            if (it != exifData.end()) {
                exifData.erase(it);
            }

            // Erase range
            if (!exifData.empty()) {
                auto beg = exifData.begin();
                auto end = exifData.end();
                if (beg != end) {
                    exifData.erase(beg, end);
                }
            }
        }

        // Test begin and end iterators
        auto beginIt = exifData.begin();
        auto endIt = exifData.end();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}