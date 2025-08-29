// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType::toFloat at value.hpp:1620:21 in value.hpp
// Exiv2::LangAltValue::toFloat at value.cpp:731:21 in value.hpp
// Exiv2::Iptcdatum::toFloat at iptc.cpp:144:18 in iptc.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat at value.hpp:1634:36 in value.hpp
// Exiv2::Exifdatum::toFloat at exif.cpp:348:18 in exif.hpp
// Exiv2::ValueType<std::pair<int, int>>::toFloat at value.hpp:1626:35 in value.hpp
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
#include <exiv2/iptc.hpp>
#include <exiv2/exif.hpp>
#include <fstream>
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    try {
        // Test Exiv2::ValueType::toFloat
        {
            Exiv2::ValueType<int> val(42);
            val.toFloat(0);
        }

        // Test Exiv2::LangAltValue::toFloat
        {
            Exiv2::LangAltValue langAlt("test");
            langAlt.toFloat(0);
        }

        // Test Exiv2::Iptcdatum::toFloat
        {
            Exiv2::IptcKey key("Iptc.Application2.Keywords");
            Exiv2::Iptcdatum datum(key);
            datum.toFloat(0);
        }

        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat
        {
            std::pair<unsigned int, unsigned int> pair(1, 2);
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> val(pair);
            val.toFloat(0);
        }

        // Test Exiv2::Exifdatum::toFloat
        {
            Exiv2::ExifKey key("Exif.Image.ImageDescription");
            Exiv2::Exifdatum datum(key);
            datum.toFloat(0);
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toFloat
        {
            std::pair<int, int> pair(1, 2);
            Exiv2::ValueType<std::pair<int, int>> val(pair);
            val.toFloat(0);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}