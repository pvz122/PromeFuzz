// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::typeId at value.hpp:85:10 in value.hpp
// Exiv2::Exifdatum::typeId at exif.cpp:316:19 in exif.hpp
// Exiv2::TypeInfo::typeId at types.cpp:77:18 in types.hpp
// Exiv2::TypeInfo::typeSize at types.cpp:83:18 in types.hpp
// Exiv2::ExifKey::defaultTypeId at tags.cpp:307:17 in tags.hpp
// Exiv2::IptcDataSets::dataSetType at datasets.cpp:404:22 in datasets.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/datasets.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_258(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize dummy values
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
    Exiv2::ExifKey key("Exif.Image.Make");
    Exiv2::Exifdatum exifDatum(key);
    std::string typeName("asciiString");
    uint16_t number = static_cast<uint16_t>(Data[0]);
    uint16_t recordId = static_cast<uint16_t>(Data[0]);

    // Call target functions
    (void)value->typeId();
    (void)exifDatum.typeId();
    (void)Exiv2::TypeInfo::typeId(typeName);
    (void)Exiv2::TypeInfo::typeSize(Exiv2::asciiString);
    (void)key.defaultTypeId();
    (void)Exiv2::IptcDataSets::dataSetType(number, recordId);

    return 0;
}