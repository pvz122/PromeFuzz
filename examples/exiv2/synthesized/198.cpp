// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::write at value.cpp:205:32 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_198(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummy(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::StringValueBase::write
        Exiv2::StringValue stringValue(dummy);
        stringValue.write(os);

        // Test Exiv2::CommentValue::write
        Exiv2::CommentValue commentValue(dummy);
        commentValue.write(os);

        // Test Exiv2::ValueType::write
        Exiv2::AsciiValue asciiValue(dummy);
        asciiValue.write(os);

        // Test Exiv2::TimeValue::write
        Exiv2::TimeValue timeValue(12, 30, 45, 5, 30);
        timeValue.write(os);

        // Test Exiv2::DataValue::write
        Exiv2::DataValue dataValue(Data, Size);
        dataValue.write(os);

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}