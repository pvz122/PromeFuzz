// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::setPacket at xmp_exiv2.hpp:228:8 in xmp_exiv2.hpp
// Exiv2::XmpSidecar::mimeType at xmpsidecar.cpp:30:25 in xmpsidecar.hpp
// Exiv2::XmpKey::tagName at properties.cpp:5180:21 in properties.hpp
// Exiv2::Xmpdatum::tagName at xmp.cpp:320:23 in xmp_exiv2.hpp
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
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/riffvideo.hpp>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_525(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::XmpData::setPacket
    try {
        Exiv2::XmpData xmpData;
        std::string xmpPacket(reinterpret_cast<const char*>(Data), Size);
        xmpData.setPacket(xmpPacket);
    } catch (...) {}

    // Test Exiv2::XmpSidecar::mimeType
    try {
        Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
        Exiv2::XmpSidecar xmpSidecar(std::move(io), true);
        xmpSidecar.mimeType();
    } catch (...) {}

    // Test Exiv2::XmpKey::tagName
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        key.tagName();
    } catch (...) {}

    // Test Exiv2::Xmpdatum::tagName
    try {
        Exiv2::XmpKey key("Xmp.dc.subject");
        Exiv2::Xmpdatum xmpDatum(key);
        xmpDatum.tagName();
    } catch (...) {}

    // Test Exiv2::XmpData::xmpPacket
    try {
        Exiv2::XmpData xmpData;
        xmpData.xmpPacket();
    } catch (...) {}

    return 0;
}