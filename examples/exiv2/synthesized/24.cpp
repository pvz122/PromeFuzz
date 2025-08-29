// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifKey::groupName at tags.cpp:287:22 in tags.hpp
// Exiv2::ExifTags::sectionName at tags.cpp:76:23 in tags.hpp
// Exiv2::ExifKey::familyName at tags.cpp:283:22 in tags.hpp
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
#include <string>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        uint16_t tag = (Data[0] << 8) | Data[1];
        std::string groupName(reinterpret_cast<const char*>(Data + 2), Size - 2);

        Exiv2::ExifKey key(tag, groupName);

        std::string group = key.groupName();
        const char* section = Exiv2::ExifTags::sectionName(key);
        const char* family = key.familyName();

        (void)group;
        (void)section;
        (void)family;
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}