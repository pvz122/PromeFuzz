// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifKey::key at tags.cpp:279:22 in tags.hpp
// Exiv2::ExifKey::tagLabel at tags.cpp:295:22 in tags.hpp
// Exiv2::ExifKey::tagName at tags.cpp:291:22 in tags.hpp
// Exiv2::ExifKey::idx at tags.cpp:329:14 in tags.hpp
// Exiv2::ExifKey::tagDesc at tags.cpp:301:22 in tags.hpp
// Exiv2::ExifKey::setIdx at tags.cpp:275:15 in tags.hpp
// Exiv2::ExifKey::idx at tags.cpp:329:14 in tags.hpp
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

extern "C" int LLVMFuzzerTestOneInput_263(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy key string
        std::string keyStr(reinterpret_cast<const char*>(Data), Size);
        if (keyStr.empty()) keyStr = "Exif.Photo.ExposureTime";

        // Create ExifKey object
        Exiv2::ExifKey key(keyStr);

        // Call target functions
        (void)key.key();
        (void)key.tagLabel();
        (void)key.tagName();
        (void)key.idx();
        (void)key.tagDesc();

        // Set and get index
        int idx = static_cast<int>(Size);
        key.setIdx(idx);
        (void)key.idx();

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}