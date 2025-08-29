// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
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
#include <exiv2/metadatum.hpp>
#include <exiv2/exif.hpp>
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_630(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    try {
        std::string data(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::LangAltValue::write
        {
            Exiv2::LangAltValue value(data);
            value.write(os);
        }

        // Test Exiv2::AsciiValue::write
        {
            Exiv2::AsciiValue value(data);
            value.write(os);
        }

        // Test Exiv2::CommentValue::write
        {
            Exiv2::CommentValue value(data);
            value.write(os);
        }

        // Test Exiv2::TimeValue::write
        {
            int32_t hour = Data[0] % 24;
            int32_t minute = Data[1] % 60;
            int32_t second = Data[2] % 60;
            int32_t tzHour = (Data[3] % 24) - 12;
            int32_t tzMinute = Data[4] % 60;
            Exiv2::TimeValue value(hour, minute, second, tzHour, tzMinute);
            value.write(os);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}