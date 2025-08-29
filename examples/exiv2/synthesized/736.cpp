// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::xmpPacket at xmp_exiv2.hpp:233:36 in xmp_exiv2.hpp
// Exiv2::XmpData::clear at xmp.cpp:448:15 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:435:14 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
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
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_736(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Test begin() and end()
        auto beginIt = xmpData.begin();
        auto endIt = xmpData.end();

        // Test xmpPacket()
        const std::string& packet = xmpData.xmpPacket();

        // Test clear()
        xmpData.clear();

        // Create a dummy XmpKey and Xmpdatum
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::Xmpdatum datum(key);

        // Test add()
        xmpData.add(datum);

        // Test findKey()
        auto foundIt = xmpData.findKey(key);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}