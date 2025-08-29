// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:195:17 in iptc.hpp
// Exiv2::Iptcdatum::toFloat at iptc.cpp:144:18 in iptc.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:254:17 in exif.hpp
// Exiv2::Exifdatum::toFloat at exif.cpp:348:18 in exif.hpp
// Exiv2::DateValue::toFloat at value.cpp:872:18 in value.hpp
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
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_733(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create basic Value
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedByte);
        value->read(Data, Size, Exiv2::littleEndian);
        (void)value->toFloat();

        // Create Iptcdatum
        Exiv2::IptcKey iptcKey("Iptc.Application2.Headline");
        Exiv2::Iptcdatum iptcDatum(iptcKey);
        Exiv2::Value::UniquePtr iptcValue = Exiv2::Value::create(Exiv2::unsignedByte);
        iptcValue->read(Data, Size, Exiv2::littleEndian);
        iptcDatum.setValue(iptcValue.get());
        (void)iptcDatum.toFloat();

        // Create Exifdatum
        Exiv2::ExifKey exifKey("Exif.Image.ImageDescription");
        Exiv2::Exifdatum exifDatum(exifKey);
        Exiv2::Value::UniquePtr exifValue = Exiv2::Value::create(Exiv2::unsignedByte);
        exifValue->read(Data, Size, Exiv2::littleEndian);
        exifDatum.setValue(exifValue.get());
        (void)exifDatum.toFloat();

        // Create DateValue
        if (Size >= 3 * sizeof(int32_t)) {
            int32_t year = *reinterpret_cast<const int32_t*>(Data);
            int32_t month = *reinterpret_cast<const int32_t*>(Data + sizeof(int32_t));
            int32_t day = *reinterpret_cast<const int32_t*>(Data + 2 * sizeof(int32_t));
            Exiv2::DateValue dateValue(year, month, day);
            (void)dateValue.toFloat();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}