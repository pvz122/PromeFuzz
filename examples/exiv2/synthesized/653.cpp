// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
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
#include <exiv2/error.hpp>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_653(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Create a dummy key and value
        std::string keyStr("Xmp.dummy.key");
        std::string valueStr(reinterpret_cast<const char*>(Data), Size);

        Exiv2::XmpKey key(keyStr);
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
        value->read(valueStr);

        // Test add()
        xmpData.add(key, value.get());

        // Test begin() and end()
        auto it_begin = xmpData.begin();
        auto it_end = xmpData.end();

        // Test findKey()
        auto found = xmpData.findKey(key);
        if (found != it_end) {
            // Test erase()
            xmpData.erase(found);
        }

        // Add another entry to test eraseFamily
        xmpData.add(key, value.get());
        found = xmpData.findKey(key);
        if (found != it_end) {
            // Test eraseFamily()
            xmpData.eraseFamily(found);
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}