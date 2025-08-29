// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
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
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_632(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummyData(reinterpret_cast<const char*>(Data), Size);
        std::stringstream ss;

        // Test Exiv2::LangAltValue::write
        {
            Exiv2::LangAltValue langAltValue(dummyData);
            langAltValue.write(ss);
        }

        // Test Exiv2::StringValueBase::write
        {
            Exiv2::StringValue stringValue(dummyData);
            stringValue.write(ss);
        }

        // Test Exiv2::DateValue::write
        {
            Exiv2::DateValue dateValue;
            dateValue.write(ss);
        }

        // Test Exiv2::XmpArrayValue::write
        {
            Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
            xmpArrayValue.write(ss);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}