// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Key::write at metadatum.hpp:71:17 in metadatum.hpp
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
// Exiv2::TimeValue::write at value.cpp:1020:26 in value.hpp
// Exiv2::DataValue::write at value.cpp:137:26 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_194(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::stringstream ss;

        // Test Exiv2::Key::write
        Exiv2::ExifKey key("Exif.Photo.UserComment");
        key.write(ss);

        // Test Exiv2::StringValueBase::write
        Exiv2::StringValue stringValue;
        stringValue.write(ss);

        // Test Exiv2::CommentValue::write
        Exiv2::CommentValue commentValue("Test comment");
        commentValue.write(ss);

        // Test Exiv2::DateValue::write
        Exiv2::DateValue dateValue;
        dateValue.write(ss);

        // Test Exiv2::TimeValue::write
        Exiv2::TimeValue timeValue(12, 30, 45, 5, 30);
        timeValue.write(ss);

        // Test Exiv2::DataValue::write
        Exiv2::DataValue dataValue(Exiv2::undefined);
        dataValue.write(ss);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}