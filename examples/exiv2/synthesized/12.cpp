// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpProperties::printProperties at properties.cpp:5091:21 in properties.hpp
// Exiv2::ExifTags::taglist at tags.cpp:114:16 in tags.hpp
// Exiv2::ExifTags::isExifGroup at tags.cpp:101:16 in tags.hpp
// Exiv2::ExifTags::taglist at tags.cpp:138:16 in tags.hpp
// Exiv2::ExifTags::groupList at tags.cpp:106:28 in tags.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/properties.hpp>
#include <exiv2/tags.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string dummyData(reinterpret_cast<const char*>(Data), Size);
    std::stringstream ss;

    try {
        // Invoke Exiv2::XmpProperties::printProperties with safe prefix
        Exiv2::XmpProperties::printProperties(ss, "exif");
    } catch (...) {
        // Ignore exceptions from invalid prefixes
    }

    // Invoke Exiv2::ExifTags::taglist (first overload)
    Exiv2::ExifTags::taglist(ss);

    try {
        // Invoke Exiv2::ExifTags::isExifGroup with safe group name
        bool isExif = Exiv2::ExifTags::isExifGroup("Image");
        (void)isExif;
    } catch (...) {
        // Ignore exceptions from invalid group names
    }

    try {
        // Invoke Exiv2::ExifTags::taglist (second overload) with safe group name
        Exiv2::ExifTags::taglist(ss, "Image");
    } catch (...) {
        // Ignore exceptions from invalid group names
    }

    // Invoke Exiv2::ExifTags::groupList
    const Exiv2::GroupInfo* groupList = Exiv2::ExifTags::groupList();
    (void)groupList;

    return 0;
}