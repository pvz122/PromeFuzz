// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifData::findKey at exif.cpp:466:30 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::erase at exif.cpp:486:30 in exif.hpp
// Exiv2::IptcData::findKey at iptc.cpp:252:30 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::IptcData::erase at iptc.cpp:274:30 in iptc.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
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
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize ExifData
        Exiv2::ExifData exifData;
        Exiv2::ExifKey exifKey("Exif.Image.Make");
        auto exifIt = exifData.findKey(exifKey);
        auto exifEnd = exifData.end();
        if (exifIt != exifEnd) {
            exifData.erase(exifIt);
        }

        // Initialize IptcData
        Exiv2::IptcData iptcData;
        Exiv2::IptcKey iptcKey("Iptc.Application2.ObjectName");
        auto iptcIt = iptcData.findKey(iptcKey);
        auto iptcEnd = iptcData.end();
        if (iptcIt != iptcEnd) {
            iptcData.erase(iptcIt);
        }

        // Initialize XmpData
        Exiv2::XmpData xmpData;
        Exiv2::XmpKey xmpKey("Xmp.dc.title");
        auto xmpIt = xmpData.findKey(xmpKey);
        if (xmpIt != xmpData.end()) {
            xmpData.eraseFamily(xmpIt);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}