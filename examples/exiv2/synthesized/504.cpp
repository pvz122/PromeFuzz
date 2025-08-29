// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
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
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_504(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummy_data(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::XmpTextValue::write
        Exiv2::XmpTextValue xmpTextValue(dummy_data);
        xmpTextValue.write(os);

        // Test Exiv2::StringValueBase::write
        Exiv2::StringValue stringValue(dummy_data);
        stringValue.write(os);

        // Test Exiv2::DateValue::write
        Exiv2::DateValue dateValue;
        dateValue.write(os);

        // Test Exiv2::DataValue::write
        Exiv2::DataValue dataValue(Data, Size);
        dataValue.write(os);

        // Test Exiv2::XmpArrayValue::write
        Exiv2::XmpArrayValue xmpArrayValue;
        xmpArrayValue.write(os);

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}