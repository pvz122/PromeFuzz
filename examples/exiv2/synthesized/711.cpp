// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::eraseFamily at xmp.cpp:484:15 in xmp_exiv2.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
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

extern "C" int LLVMFuzzerTestOneInput_711(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Add some dummy data to manipulate
        Exiv2::XmpKey key("Xmp.dc.title", "dc");
        Exiv2::StringValue value("Test Value");
        xmpData.add(key, &value);

        // Test begin() and end()
        auto beginIt = xmpData.begin();
        auto endIt = xmpData.end();

        // Test findKey()
        auto foundIt = xmpData.findKey(key);

        // Test erase() if we have at least one element
        if (beginIt != endIt) {
            xmpData.erase(beginIt);
        }

        // Test eraseFamily() if we have at least one element
        if (beginIt != endIt) {
            xmpData.eraseFamily(beginIt);
        }

        // Add more data based on fuzzer input
        std::string inputStr(reinterpret_cast<const char*>(Data), Size);
        Exiv2::XmpKey inputKey(inputStr.c_str(), "dc");
        Exiv2::StringValue inputValue(inputStr);
        xmpData.add(inputKey, &inputValue);

        // Exercise iterators again with new data
        beginIt = xmpData.begin();
        endIt = xmpData.end();
        foundIt = xmpData.findKey(inputKey);

        // Try erase operations again
        if (beginIt != endIt) {
            xmpData.erase(beginIt);
        }
        if (beginIt != endIt) {
            xmpData.eraseFamily(beginIt);
        }

    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}