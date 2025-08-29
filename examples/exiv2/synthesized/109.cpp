// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
// Exiv2::IptcDataSets::dataSetList at datasets.cpp:490:20 in datasets.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpProperties::printProperty at properties.cpp:5100:30 in properties.hpp
// Exiv2::ExifTags::taglist at tags.cpp:114:16 in tags.hpp
// Exiv2::ExifTags::taglist at tags.cpp:138:16 in tags.hpp
// Exiv2::XmpProperties::printProperties at properties.cpp:5091:21 in properties.hpp
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
#include <exiv2/properties.hpp>
#include <exiv2/datasets.hpp>
#include <exiv2/tags.hpp>
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string dummy_data(reinterpret_cast<const char*>(Data), Size);
    std::stringstream ss;

    // Test Exiv2::XmpTextValue::write
    try {
        Exiv2::XmpTextValue xmpTextValue(dummy_data);
        xmpTextValue.write(ss);
    } catch (...) {}

    // Test Exiv2::IptcDataSets::dataSetList
    try {
        Exiv2::IptcDataSets::dataSetList(ss);
    } catch (...) {}

    // Test Exiv2::XmpProperties::printProperty
    try {
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
        value->read(dummy_data);
        Exiv2::XmpProperties::printProperty(ss, dummy_data, *value);
    } catch (...) {}

    // Test Exiv2::ExifTags::taglist (both overloads)
    try {
        Exiv2::ExifTags::taglist(ss);
        Exiv2::ExifTags::taglist(ss, dummy_data);
    } catch (...) {}

    // Test Exiv2::XmpProperties::printProperties
    try {
        Exiv2::XmpProperties::printProperties(ss, dummy_data);
    } catch (...) {}

    return 0;
}