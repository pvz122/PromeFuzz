// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::sortByKey at xmp.cpp:452:15 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::empty at xmp.cpp:464:15 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::eraseFamily at xmp.cpp:484:15 in xmp_exiv2.hpp
// Exiv2::XmpData::empty at xmp.cpp:464:15 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::XmpData::count at xmp.cpp:468:15 in xmp_exiv2.hpp
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
#include <algorithm>

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    Exiv2::XmpData xmpData;

    // Create some XMP data entries with fuzzed input
    for (size_t i = 0; i < Size - 1; i += 2) {
        try {
            std::string key = "Xmp.test.Key" + std::to_string(Data[i]);
            std::string value = "Value" + std::to_string(Data[i+1]);
            Exiv2::XmpKey xmpKey(key);
            Exiv2::XmpTextValue xmpValue(value);
            xmpData.add(xmpKey, &xmpValue);
        } catch (...) {
            // Ignore invalid keys/values
        }
    }

    // Test sortByKey
    xmpData.sortByKey();

    // Test begin/end iteration
    for (auto it = xmpData.begin(); it != xmpData.end(); ++it) {
        // Just iterate through
    }

    // Test eraseFamily if we have at least one element
    if (!xmpData.empty()) {
        auto it = xmpData.begin();
        try {
            xmpData.eraseFamily(it);
        } catch (...) {
            // Ignore any errors
        }
    }

    // Test erase if we have at least one element
    if (!xmpData.empty()) {
        auto it = xmpData.begin();
        try {
            xmpData.erase(it);
        } catch (...) {
            // Ignore any errors
        }
    }

    // Test count
    (void)xmpData.count();

    return 0;
}