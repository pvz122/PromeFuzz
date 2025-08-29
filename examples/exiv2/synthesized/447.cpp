// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::write at value.cpp:526:29 in value.hpp
// Exiv2::Key::write at metadatum.hpp:71:17 in metadatum.hpp
// Exiv2::Key::write at metadatum.hpp:71:17 in metadatum.hpp
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::ValueType::write at value.hpp:1551:29 in value.hpp
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::write at value.cpp:596:30 in value.hpp
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
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_447(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string input(reinterpret_cast<const char*>(Data), Size);
        std::ostringstream os;

        // Test Exiv2::XmpTextValue::write
        Exiv2::XmpTextValue xmpTextValue(input);
        xmpTextValue.write(os);

        // Test Exiv2::Key::write
        Exiv2::ExifKey exifKey(42, "Exif.Image.ImageDescription");
        exifKey.write(os);

        Exiv2::IptcKey iptcKey("Iptc.Application2.Caption");
        iptcKey.write(os);

        // Test Exiv2::LangAltValue::write
        Exiv2::LangAltValue langAltValue(input);
        langAltValue.write(os);

        // Test Exiv2::CommentValue::write
        Exiv2::CommentValue commentValue(input);
        commentValue.write(os);

        // Test Exiv2::ValueType::write
        Exiv2::ValueType<uint16_t> valueType;
        valueType.write(os);

        // Test Exiv2::XmpArrayValue::write
        Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
        if (Size > 10) {
            xmpArrayValue.read(input);
            xmpArrayValue.write(os);
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}