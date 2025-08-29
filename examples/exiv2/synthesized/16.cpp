// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::XmpData::empty at xmp.cpp:464:15 in xmp_exiv2.hpp
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    Exiv2::XmpData xmpData;
    Exiv2::IptcData iptcData;
    Exiv2::ExifData exifData;

    (void)exifData.end();
    (void)exifData.empty();
    (void)iptcData.empty();
    (void)xmpData.empty();

    return 0;
}