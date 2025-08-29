// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpKey::key at properties.cpp:5168:21 in properties.hpp
// Exiv2::XmpKey::familyName at properties.cpp:5172:21 in properties.hpp
// Exiv2::XmpKey::groupName at properties.cpp:5176:21 in properties.hpp
// Exiv2::XmpKey::tagName at properties.cpp:5180:21 in properties.hpp
// Exiv2::XmpKey::tagLabel at properties.cpp:5184:21 in properties.hpp
// Exiv2::XmpKey::tag at properties.cpp:5198:18 in properties.hpp
// Exiv2::XmpKey::ns at properties.cpp:5202:21 in properties.hpp
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        // Split input into prefix and property parts
        size_t split_pos = Size / 2;
        std::string prefix(reinterpret_cast<const char*>(Data), split_pos);
        std::string property(reinterpret_cast<const char*>(Data + split_pos), Size - split_pos);

        // Create XmpKey
        Exiv2::XmpKey key(prefix, property);

        // Invoke functions in specified order
        (void)key.key();
        (void)key.familyName();
        (void)key.groupName();
        (void)key.tagName();
        (void)key.tagLabel();
        (void)key.tag();
        (void)key.ns();
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}