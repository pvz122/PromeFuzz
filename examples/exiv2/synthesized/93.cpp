// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::setPacket at xmp_exiv2.hpp:228:8 in xmp_exiv2.hpp
// Exiv2::XmpData::xmpPacket at xmp_exiv2.hpp:233:36 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::tagName at xmp.cpp:320:23 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::groupName at xmp.cpp:316:23 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::tagDesc at xmp.cpp:328:23 in xmp_exiv2.hpp
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
#include <exiv2/riffvideo.hpp>
#include <exiv2/exiv2.hpp>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2 XmpData
    Exiv2::XmpData xmpData;
    try {
        std::string xmpPacket(reinterpret_cast<const char*>(Data), Size);
        xmpData.setPacket(xmpPacket);
        xmpData.xmpPacket();
    } catch (...) {}

    // Test Xmpdatum functions
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::Xmpdatum xmpDatum(key);
        xmpDatum.tagName();
        xmpDatum.groupName();
        xmpDatum.tagDesc();
    } catch (...) {}

    // Skip RiffVideo::HeaderReader test since it's protected
    return 0;
}