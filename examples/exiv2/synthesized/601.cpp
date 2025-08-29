// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::eraseFamily at xmp.cpp:484:15 in xmp_exiv2.hpp
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

extern "C" int LLVMFuzzerTestOneInput_601(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Add some dummy data to manipulate
        Exiv2::XmpKey key("dc", "title");
        Exiv2::XmpTextValue value("dummy");
        xmpData.add(key, &value);

        // Test begin() and end()
        auto it_begin = xmpData.begin();
        auto it_end = xmpData.end();

        // Test findKey()
        auto it_find = xmpData.findKey(key);

        // Test erase() if we have at least one element
        if (it_begin != it_end) {
            xmpData.erase(it_begin);
        }

        // Add another element to test eraseFamily
        Exiv2::XmpKey key2("dc", "description");
        Exiv2::XmpTextValue value2("dummy2");
        xmpData.add(key2, &value2);

        auto it_begin2 = xmpData.begin();
        if (it_begin2 != xmpData.end()) {
            xmpData.eraseFamily(it_begin2);
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}