// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::clear at xmp.cpp:448:15 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::clear at xmp.cpp:448:15 in xmp_exiv2.hpp
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
#include <exiv2/error.hpp>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    try {
        Exiv2::XmpData xmpData;

        // Add some dummy data to the XmpData
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::StringValue value("Test Title");
        xmpData.add(key, &value);

        // Test begin()
        auto it_begin = xmpData.begin();

        // Test end()
        auto it_end = xmpData.end();

        // Test findKey()
        auto it_find = xmpData.findKey(key);

        // Test erase()
        if (it_begin != it_end) {
            xmpData.erase(it_begin);
        }

        // Test clear()
        xmpData.clear();

        // Add more data to test again
        if (Size > 0) {
            std::string str(reinterpret_cast<const char*>(Data), Size);
            Exiv2::StringValue newValue(str);
            xmpData.add(key, &newValue);

            // Test begin() again
            it_begin = xmpData.begin();

            // Test end() again
            it_end = xmpData.end();

            // Test findKey() again
            it_find = xmpData.findKey(key);

            // Test erase() again
            if (it_begin != it_end) {
                xmpData.erase(it_begin);
            }

            // Test clear() again
            xmpData.clear();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}