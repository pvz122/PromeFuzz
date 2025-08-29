// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifKey::tagName at tags.cpp:291:22 in tags.hpp
// Exiv2::ExifKey::tag at tags.cpp:313:19 in tags.hpp
// Exiv2::ExifTags::ifdName at tags.cpp:91:23 in tags.hpp
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

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy ExifKey
        std::string groupName(reinterpret_cast<const char*>(Data), Size);
        Exiv2::ExifKey key(groupName);

        // Invoke functions in specified order
        std::string tagName = key.tagName();
        uint16_t tag = key.tag();
        const char* ifdName = Exiv2::ExifTags::ifdName(groupName);

        (void)tagName;
        (void)tag;
        (void)ifdName;
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}