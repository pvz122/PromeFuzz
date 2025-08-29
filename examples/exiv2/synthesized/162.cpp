// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Exifdatum::typeName at exif.cpp:320:24 in exif.hpp
// Exiv2::Exifdatum::groupName at exif.cpp:280:24 in exif.hpp
// Exiv2::Exifdatum::ifdName at exif.cpp:304:24 in exif.hpp
// Exiv2::Exifdatum::familyName at exif.cpp:276:24 in exif.hpp
// Exiv2::Exifdatum::ifdId at exif.cpp:300:18 in exif.hpp
// Exiv2::ExifKey::ifdId at tags.cpp:325:16 in tags.hpp
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

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy ExifKey
        Exiv2::ExifKey key("Exif.Image.Make");
        Exiv2::Exifdatum datum(key);

        // Call the target functions
        (void)datum.typeName();
        (void)datum.groupName();
        (void)datum.ifdName();
        (void)datum.familyName();
        (void)datum.ifdId();

        // Also test ExifKey::ifdId
        (void)key.ifdId();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}