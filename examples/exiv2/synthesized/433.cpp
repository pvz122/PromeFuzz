// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:435:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:440:34 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
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
#include <string>
#include <fstream>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_433(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Add some dummy data to manipulate
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::Xmpdatum datum(key);
        xmpData.add(datum);

        // Test begin() and end()
        auto beginIt = xmpData.begin();
        auto endIt = xmpData.end();

        // Test erase()
        if (beginIt != endIt) {
            xmpData.erase(beginIt);
        }

        // Test findKey() - const and non-const versions
        const Exiv2::XmpData& constXmpData = xmpData;
        auto foundIt = xmpData.findKey(key);
        auto constFoundIt = constXmpData.findKey(key);

        // Test add() with key-value pair
        std::unique_ptr<Exiv2::Value> value(Exiv2::Value::create(Exiv2::xmpText));
        value->read("test");
        xmpData.add(key, value.get());

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}