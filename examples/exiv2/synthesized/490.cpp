// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
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
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_490(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::ostringstream os;

    try {
        // Test LangAltValue::write
        Exiv2::LangAltValue langAltValue(input);
        langAltValue.write(os);

        // Test AsciiValue::write
        Exiv2::AsciiValue asciiValue;
        asciiValue.write(os);

        // Test CommentValue::write
        Exiv2::CommentValue commentValue(input);
        commentValue.write(os);

        // Test DateValue::write
        Exiv2::DateValue dateValue;
        dateValue.write(os);

        // Test TimeValue::write
        Exiv2::TimeValue timeValue;
        timeValue.write(os);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}