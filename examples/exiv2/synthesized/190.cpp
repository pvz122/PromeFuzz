// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::ValueType::write at value.hpp:1551:29 in value.hpp
// Exiv2::TimeValue::write at value.cpp:1020:26 in value.hpp
// Exiv2::DataValue::write at value.cpp:137:26 in value.hpp
// Exiv2::XmpArrayValue::write at value.cpp:596:30 in value.hpp
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
#include <exiv2/metadatum.hpp>
#include <exiv2/exif.hpp>
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_190(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummyData(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::StringValueBase::write
        Exiv2::StringValue stringValue(dummyData);
        stringValue.write(os);

        // Test Exiv2::ValueType::write
        Exiv2::ValueType<int> valueType;
        valueType.write(os);

        // Test Exiv2::TimeValue::write
        Exiv2::TimeValue timeValue;
        timeValue.write(os);

        // Test Exiv2::DataValue::write
        Exiv2::DataValue dataValue;
        dataValue.write(os);

        // Test Exiv2::XmpArrayValue::write
        Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
        xmpArrayValue.write(os);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}