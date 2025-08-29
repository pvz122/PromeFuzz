// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::exposureBiasValue at easyaccess.cpp:414:26 in easyaccess.hpp
// Exiv2::sensingMethod at easyaccess.cpp:507:26 in easyaccess.hpp
// Exiv2::fNumber at easyaccess.cpp:379:26 in easyaccess.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
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

extern "C" int LLVMFuzzerTestOneInput_421(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::ExifData exifData;

        // Create a dummy ExifKey
        Exiv2::TagInfo tagInfo;
        tagInfo.tag_ = 0x1234;
        tagInfo.ifdId_ = Exiv2::IfdId::ifd0Id;
        tagInfo.name_ = "TestTag";
        Exiv2::ExifKey exifKey(tagInfo);

        // Test findKey
        exifData.findKey(exifKey);

        // Test begin and end
        auto it_begin = exifData.begin();
        auto it_end = exifData.end();

        // Test exposureBiasValue
        Exiv2::exposureBiasValue(exifData);

        // Test sensingMethod
        Exiv2::sensingMethod(exifData);

        // Test fNumber
        Exiv2::fNumber(exifData);

        // Add some dummy data to test iterators
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
        value->read("42");
        Exiv2::Exifdatum exifDatum(exifKey, value.get());
        exifData.add(exifDatum);

        // Test iterators again with data
        it_begin = exifData.begin();
        it_end = exifData.end();

        // Test findKey with existing key
        exifData.findKey(exifKey);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}