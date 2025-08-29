// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::TimeValue::write at value.cpp:1020:26 in value.hpp
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
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_565(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string input(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::XmpTextValue::write
        Exiv2::XmpTextValue xmpTextValue;
        xmpTextValue.write(os);

        // Test Exiv2::LangAltValue::write
        Exiv2::LangAltValue langAltValue;
        langAltValue.write(os);

        // Test Exiv2::AsciiValue::write
        Exiv2::AsciiValue asciiValue(input);
        asciiValue.write(os);

        // Test Exiv2::StringValue::write
        Exiv2::StringValue stringValue;
        stringValue.write(os);

        // Test Exiv2::TimeValue::write
        Exiv2::TimeValue timeValue;
        timeValue.write(os);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}