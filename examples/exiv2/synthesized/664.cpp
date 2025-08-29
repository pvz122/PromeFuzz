// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
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
#include <exiv2/iptc.hpp>
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_664(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy file
        std::ofstream dummy_file("./dummy_file", std::ios::binary);
        dummy_file.write(reinterpret_cast<const char*>(Data), Size);
        dummy_file.close();

        // Initialize objects
        Exiv2::DateValue dateValue;
        Exiv2::CommentValue commentValue;
        Exiv2::AsciiValue asciiValue;
        Exiv2::StringValue stringValue(std::string(reinterpret_cast<const char*>(Data), Size));

        // Create output streams
        std::ostringstream oss1, oss2, oss3, oss4;

        // Call write functions
        asciiValue.write(oss1);
        commentValue.write(oss2);
        dateValue.write(oss3);
        stringValue.write(oss4);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}