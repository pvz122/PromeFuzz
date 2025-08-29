// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
// Exiv2::Key::write at metadatum.hpp:71:17 in metadatum.hpp
// Exiv2::Key::write at metadatum.hpp:71:17 in metadatum.hpp
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::LangAltValue::clone at value.cpp:679:39 in value.hpp
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_233(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy file
        std::ofstream dummyFile("./dummy_file", std::ios::binary);
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();

        // Test XmpTextValue::write
        {
            Exiv2::XmpTextValue value(std::string(reinterpret_cast<const char*>(Data), Size));
            value.write(std::cout);
        }

        // Test Key::write
        {
            Exiv2::ExifKey exifKey("Exif.Photo.UserComment");
            exifKey.write(std::cout);

            Exiv2::IptcKey iptcKey(1, 1);
            iptcKey.write(std::cout);
        }

        // Test LangAltValue::write and clone
        {
            Exiv2::LangAltValue value(std::string(reinterpret_cast<const char*>(Data), Size));
            value.write(std::cout);
            auto cloned = value.clone();
            cloned->write(std::cout);
        }

        // Test DateValue::write
        {
            Exiv2::DateValue value;
            value.write(std::cout);
        }

        // Test ValueType::write
        {
            Exiv2::XmpTextValue textValue(std::string(reinterpret_cast<const char*>(Data), Size));
            textValue.write(std::cout);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}