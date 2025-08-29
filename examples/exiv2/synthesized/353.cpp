// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::clone at value.hpp:265:13 in value.hpp
// Exiv2::XmpKey::clone at properties.cpp:5160:27 in properties.hpp
// Exiv2::StringValue::clone at value.hpp:394:13 in value.hpp
// Exiv2::XmpArrayValue::clone at value.cpp:588:41 in value.hpp
// Exiv2::ExifKey::clone at tags.cpp:317:29 in tags.hpp
// Exiv2::StringValueBase::clone at value.hpp:336:13 in value.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_353(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create DataValue
        Exiv2::DataValue dataValue(Data, Size);
        auto dataValueClone = dataValue.clone();

        // Create XmpKey
        std::string prefix("prefix");
        std::string property("property");
        Exiv2::XmpKey xmpKey(prefix, property);
        auto xmpKeyClone = xmpKey.clone();

        // Create StringValue
        std::string strValue(reinterpret_cast<const char*>(Data), Size);
        Exiv2::StringValue stringValue(strValue);
        auto stringValueClone = stringValue.clone();

        // Create XmpArrayValue
        Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
        auto xmpArrayValueClone = xmpArrayValue.clone();

        // Create Key (using ExifKey as concrete implementation)
        std::string exifKeyStr("Exif.Photo.ExposureTime");
        Exiv2::ExifKey exifKey(exifKeyStr);
        auto exifKeyClone = exifKey.clone();

        // Create StringValueBase (using StringValue as concrete implementation)
        Exiv2::StringValueBase& stringValueBase = stringValue;
        auto stringValueBaseClone = stringValueBase.clone();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}