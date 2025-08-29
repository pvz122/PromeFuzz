// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpKey::tagLabel at properties.cpp:5184:21 in properties.hpp
// Exiv2::XmpKey::tagDesc at properties.cpp:5191:21 in properties.hpp
// Exiv2::XmpKey::groupName at properties.cpp:5176:21 in properties.hpp
// Exiv2::XmpKey::ns at properties.cpp:5202:21 in properties.hpp
// Exiv2::XmpKey::tagName at properties.cpp:5180:21 in properties.hpp
// Exiv2::XmpKey::key at properties.cpp:5168:21 in properties.hpp
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
#include <vector>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_171(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy key string from fuzzer input
        std::string keyStr(reinterpret_cast<const char*>(Data), Size);
        keyStr = "Xmp." + keyStr; // Ensure it starts with Xmp.

        // Create XmpKey object
        Exiv2::XmpKey key(keyStr);

        // Call all target functions
        (void)key.tagLabel();
        (void)key.tagDesc();
        (void)key.groupName();
        (void)key.ns();
        (void)key.tagName();
        (void)key.key();

    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    } catch (...) {
        // Ignore all other exceptions
    }

    return 0;
}