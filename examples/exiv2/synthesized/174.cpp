// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::IptcKey::familyName at datasets.cpp:510:22 in datasets.hpp
// Exiv2::Iptcdatum::familyName at iptc.cpp:88:24 in iptc.hpp
// Exiv2::IptcData::detectCharset at iptc.cpp:305:23 in iptc.hpp
// Exiv2::IptcDataSets::dataSetDesc at datasets.cpp:425:27 in datasets.hpp
// Exiv2::copyIptcToXmp at convert.cpp:1355:6 in convert.hpp
// Exiv2::moveIptcToXmp at convert.cpp:1366:6 in convert.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_174(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // Test Exiv2::IptcKey::familyName
        Exiv2::IptcKey key("Iptc.Application2.Keywords");
        const char* family = key.familyName();
        (void)family; // Avoid unused variable warning

        // Test Exiv2::Iptcdatum::familyName
        Exiv2::IptcData iptcData;
        Exiv2::StringValue value("test");
        Exiv2::Iptcdatum datum(key, &value);
        const char* datumFamily = datum.familyName();
        (void)datumFamily; // Avoid unused variable warning

        // Test Exiv2::IptcData::detectCharset
        const char* charset = iptcData.detectCharset();
        (void)charset; // Avoid unused variable warning

        // Test Exiv2::IptcDataSets::dataSetDesc
        uint16_t number = static_cast<uint16_t>(Data[0] % 256);
        uint16_t recordId = static_cast<uint16_t>(Data[0] % 256);
        const char* desc = Exiv2::IptcDataSets::dataSetDesc(number, recordId);
        (void)desc; // Avoid unused variable warning

        // Test Exiv2::copyIptcToXmp and Exiv2::moveIptcToXmp
        Exiv2::XmpData xmpData;
        Exiv2::copyIptcToXmp(iptcData, xmpData);
        Exiv2::moveIptcToXmp(iptcData, xmpData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}