// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:435:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:435:14 in xmp_exiv2.hpp
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
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_657(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Create some XMP data to work with
        std::string prefix("prefix");
        std::string property("property");
        std::string value(Data, Data + Size);

        Exiv2::XmpKey key(prefix, property);
        Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpText);
        val->read(value);
        Exiv2::Xmpdatum datum(key, val.get());

        xmpData.add(datum);

        // Test begin() and end()
        auto it_begin = xmpData.begin();
        auto it_end = xmpData.end();

        if (it_begin != it_end) {
            // Test findKey()
            auto found = xmpData.findKey(key);
            if (found != it_end) {
                // Test erase()
                xmpData.erase(found);

                // Add another datum to test eraseFamily
                Exiv2::XmpKey key2("prefix2", "property2");
                Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::xmpText);
                val2->read(value);
                Exiv2::Xmpdatum datum2(key2, val2.get());
                xmpData.add(datum2);

                auto it = xmpData.begin();
                if (it != xmpData.end()) {
                    // Test eraseFamily()
                    xmpData.eraseFamily(it);
                }
            }
        }
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}