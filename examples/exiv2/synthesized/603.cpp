// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::eraseFamily at xmp.cpp:484:15 in xmp_exiv2.hpp
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
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_603(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Create some XMP data to work with
        Exiv2::XmpKey key1("dc", "title");
        Exiv2::StringValue value1("Test Title");
        xmpData.add(key1, &value1);

        Exiv2::XmpKey key2("dc", "creator");
        Exiv2::StringValue value2("Test Creator");
        xmpData.add(key2, &value2);

        // Test begin() and end()
        auto it_begin = xmpData.begin();
        auto it_end = xmpData.end();

        // Test findKey()
        auto found_it = xmpData.findKey(key1);

        // Test erase() if we have at least one element
        if (it_begin != it_end) {
            xmpData.erase(it_begin);
        }

        // Test eraseFamily() if we have at least one element
        if (xmpData.begin() != xmpData.end()) {
            auto it = xmpData.begin();
            xmpData.eraseFamily(it);
        }

        // Add more data with fuzzed input
        std::string prefix(reinterpret_cast<const char*>(Data), Size/2);
        std::string property(reinterpret_cast<const char*>(Data + Size/2), Size - Size/2);
        
        try {
            Exiv2::XmpKey fuzzKey(prefix, property);
            Exiv2::StringValue fuzzValue("Fuzzed Value");
            xmpData.add(fuzzKey, &fuzzValue);
        } catch (...) {
            // Ignore key creation errors
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}