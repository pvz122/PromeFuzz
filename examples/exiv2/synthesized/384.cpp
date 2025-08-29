// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
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
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_384(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Prepare dummy file
        std::ofstream dummy_file("./dummy_file", std::ios::binary);
        dummy_file.write(reinterpret_cast<const char*>(Data), Size);
        dummy_file.close();

        std::ostringstream os;

        // Test AsciiValue::write
        Exiv2::AsciiValue asciiValue;
        asciiValue.write(os);

        // Test StringValueBase::write
        Exiv2::StringValue stringValue(std::string(reinterpret_cast<const char*>(Data), Size));
        stringValue.write(os);

        // Test CommentValue::write
        Exiv2::CommentValue commentValue;
        commentValue.write(os);

        // Test DateValue::write
        Exiv2::DateValue dateValue;
        dateValue.write(os);

        // Test TimeValue::write
        Exiv2::TimeValue timeValue(12, 30, 45, 5, 30);
        timeValue.write(os);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}