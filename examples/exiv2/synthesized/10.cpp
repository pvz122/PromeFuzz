// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::TypeInfo::typeName at types.cpp:71:23 in types.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::ExifData::add at exif.cpp:453:16 in exif.hpp
// Exiv2::IptcData::add at iptc.cpp:234:15 in iptc.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::TypeInfo::typeName at types.cpp:71:23 in types.hpp
// Exiv2::Value::typeId at value.hpp:85:10 in value.hpp
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
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // First call to typeName
        const char* typeName1 = Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));

        // Create a Value
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));

        // Create ExifKey and add to ExifData
        Exiv2::ExifData exifData;
        Exiv2::ExifKey exifKey("Exif.Image.Make");
        exifData.add(exifKey, value.get());

        // Create IptcKey and add to IptcData
        Exiv2::IptcData iptcData;
        Exiv2::IptcKey iptcKey("Iptc.Application2.ObjectName");
        iptcData.add(iptcKey, value.get());

        // Create XmpKey and add to XmpData
        Exiv2::XmpData xmpData;
        Exiv2::XmpKey xmpKey("Xmp.dc.title");
        xmpData.add(xmpKey, value.get());

        // Second call to typeName
        const char* typeName2 = Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));

        // Call typeId
        Exiv2::TypeId typeId = value->typeId();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}