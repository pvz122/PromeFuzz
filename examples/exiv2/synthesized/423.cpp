// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::toFloat at value.cpp:731:21 in value.hpp
// Exiv2::Exifdatum::toFloat at exif.cpp:348:18 in exif.hpp
// Exiv2::DateValue::toFloat at value.cpp:872:18 in value.hpp
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
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_423(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::LangAltValue::toFloat
        {
            Exiv2::LangAltValue value("test");
            (void)value.toFloat();
        }

        // Test Exiv2::Exifdatum::toFloat
        {
            Exiv2::ExifKey key("Exif.Image.ImageWidth");
            Exiv2::Exifdatum datum(key);
            (void)datum.toFloat();
        }

        // Test Exiv2::DateValue::toFloat
        {
            Exiv2::DateValue value(2023, 1, 1);
            (void)value.toFloat();
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}