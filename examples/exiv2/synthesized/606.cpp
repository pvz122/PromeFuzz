// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType::toFloat at value.hpp:1620:21 in value.hpp
// Exiv2::Xmpdatum::toFloat at xmp.cpp:368:17 in xmp_exiv2.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat at value.hpp:1634:36 in value.hpp
// Exiv2::Exifdatum::toFloat at exif.cpp:348:18 in exif.hpp
// Exiv2::ValueType<std::pair<int, int>>::toFloat at value.hpp:1626:35 in value.hpp
// Exiv2::TimeValue::toFloat at value.cpp:1050:18 in value.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_606(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::ValueType::toFloat
        {
            Exiv2::ValueType<int> valueType(Data, Size, Exiv2::littleEndian);
            (void)valueType.toFloat();
        }

        // Test Exiv2::Xmpdatum::toFloat
        {
            Exiv2::XmpKey key("Xmp.dc.title");
            Exiv2::Xmpdatum xmpDatum(key);
            (void)xmpDatum.toFloat();
        }

        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat
        {
            std::pair<unsigned int, unsigned int> pair = {1, 2};
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueType(pair);
            (void)valueType.toFloat();
        }

        // Test Exiv2::Exifdatum::toFloat
        {
            Exiv2::ExifKey key("Exif.Image.Orientation");
            Exiv2::Exifdatum exifDatum(key);
            (void)exifDatum.toFloat();
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toFloat
        {
            std::pair<int, int> pair = {1, 2};
            Exiv2::ValueType<std::pair<int, int>> valueType(pair);
            (void)valueType.toFloat();
        }

        // Test Exiv2::TimeValue::toFloat
        {
            Exiv2::TimeValue timeValue;
            (void)timeValue.toFloat();
        }
    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}