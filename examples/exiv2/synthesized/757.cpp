// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpKey::tagLabel at properties.cpp:5184:21 in properties.hpp
// Exiv2::XmpKey::ns at properties.cpp:5202:21 in properties.hpp
// Exiv2::XmpKey::tagName at properties.cpp:5180:21 in properties.hpp
// Exiv2::XmpData::setPacket at xmp_exiv2.hpp:228:8 in xmp_exiv2.hpp
// Exiv2::XmpData::xmpPacket at xmp_exiv2.hpp:233:36 in xmp_exiv2.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/error.hpp>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_757(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::XmpKey functions
        std::string keyStr(reinterpret_cast<const char*>(Data), Size);
        Exiv2::XmpKey xmpKey(keyStr);
        (void)xmpKey.tagLabel();
        (void)xmpKey.ns();
        (void)xmpKey.tagName();

        // Test Exiv2::XmpData functions
        Exiv2::XmpData xmpData;
        xmpData.setPacket(keyStr);
        (void)xmpData.xmpPacket();

    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    }

    return 0;
}