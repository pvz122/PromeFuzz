// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:440:34 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
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
#include <vector>
#include <string>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_307(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        // Initialize XmpData
        Exiv2::XmpData xmpData;

        // Create some XmpKey and Value objects to populate the XmpData
        std::string prefix(reinterpret_cast<const char*>(Data), 1);
        std::string property(reinterpret_cast<const char*>(Data + 1), 1);
        Exiv2::XmpKey key(prefix, property);

        std::unique_ptr<Exiv2::Value> value = Exiv2::Value::create(Exiv2::asciiString);
        std::string buf(reinterpret_cast<const char*>(Data), Size);
        value->read(buf);

        // Test add function
        xmpData.add(key, value.get());

        // Test begin and end functions
        auto beginIt = xmpData.begin();
        auto endIt = xmpData.end();

        // Test findKey function (both const and non-const versions)
        const Exiv2::XmpData& constXmpData = xmpData;
        auto foundItConst = constXmpData.findKey(key);
        auto foundItNonConst = xmpData.findKey(key);

        // Test erase function if we have at least one element
        if (beginIt != endIt) {
            xmpData.erase(beginIt);
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}