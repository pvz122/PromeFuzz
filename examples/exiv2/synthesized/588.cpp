// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:457:16 in exif.hpp
// Exiv2::exposureTime at easyaccess.cpp:371:26 in easyaccess.hpp
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::serialNumber at easyaccess.cpp:460:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::fNumber at easyaccess.cpp:379:26 in easyaccess.hpp
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

extern "C" int LLVMFuzzerTestOneInput_588(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::ExifData ed;

        // Create a dummy ExifKey
        Exiv2::ExifKey key("Exif.Photo.ExposureTime");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedRational);
        value->read(Data, Size, Exiv2::littleEndian);
        Exiv2::Exifdatum datum(key, value.get());
        ed.add(datum);

        // Test exposureTime
        Exiv2::exposureTime(ed);

        // Test findKey
        ed.findKey(key);

        // Test begin
        ed.begin();

        // Test serialNumber
        Exiv2::serialNumber(ed);

        // Test end
        ed.end();

        // Test fNumber
        Exiv2::fNumber(ed);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}