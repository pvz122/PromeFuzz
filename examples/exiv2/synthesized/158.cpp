// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Xmpdatum::toString at xmp.cpp:356:23 in xmp_exiv2.hpp
// Exiv2::toStringHelper at types.hpp:456:13 in types.hpp
// Exiv2::toStringHelper at types.hpp:461:13 in types.hpp
// Exiv2::parseRational at types.cpp:590:10 in types.hpp
// Exiv2::toString at types.hpp:467:13 in types.hpp
// Exiv2::Exifdatum::toString at exif.cpp:336:24 in exif.hpp
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
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <fstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::Xmpdatum::toString
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::Xmpdatum xmpDatum(key);
        (void)xmpDatum.toString();
    } catch (...) {}

    // Test Exiv2::toStringHelper
    try {
        int intVal = 42;
        (void)Exiv2::toStringHelper(intVal, std::true_type{});
        (void)Exiv2::toStringHelper(intVal, std::false_type{});
    } catch (...) {}

    // Test Exiv2::parseRational
    try {
        bool ok = false;
        std::string rationalStr(reinterpret_cast<const char*>(Data), Size);
        (void)Exiv2::parseRational(rationalStr, ok);
    } catch (...) {}

    // Test Exiv2::toString
    try {
        int intVal = 42;
        (void)Exiv2::toString(intVal);
    } catch (...) {}

    // Test Exiv2::Exifdatum::toString
    try {
        Exiv2::ExifKey key("Exif.Image.ImageWidth");
        Exiv2::Exifdatum exifDatum(key);
        (void)exifDatum.toString();
    } catch (...) {}

    return 0;
}