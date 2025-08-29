// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType::toFloat at value.hpp:1620:21 in value.hpp
// Exiv2::XmpValue::read at value.cpp:463:15 in value.hpp
// Exiv2::XmpArrayValue::toFloat at value.cpp:617:22 in value.hpp
// Exiv2::XmpTextValue::toFloat at value.cpp:566:21 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat at value.hpp:1634:36 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
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
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_564(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy data for ValueType<unsignedShort>
        std::vector<Exiv2::byte> buffer(Data, Data + Size);
        Exiv2::ValueType<unsigned short> valueType(buffer.data(), buffer.size(), Exiv2::littleEndian, Exiv2::unsignedShort);
        (void)valueType.toFloat();

        // Create XmpArrayValue
        Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
        if (Size > 4) {
            xmpArrayValue.read(Data, Size);
            (void)xmpArrayValue.toFloat();
        }

        // Create XmpTextValue
        std::string textValue(reinterpret_cast<const char*>(Data), Size);
        Exiv2::XmpTextValue xmpTextValue(textValue);
        (void)xmpTextValue.toFloat();

        // Create ValueType with pair<unsigned int, unsigned int>
        std::pair<unsigned int, unsigned int> uintPair(Size, Size * 2);
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairValue(
            reinterpret_cast<const Exiv2::byte*>(&uintPair), 
            sizeof(uintPair), 
            Exiv2::littleEndian
        );
        (void)uintPairValue.toFloat();

        // Create Exifdatum
        Exiv2::ExifKey key("Exif.Image.ImageWidth");
        Exiv2::Exifdatum exifDatum(key);
        if (Size > 8) {
            exifDatum.setValue(std::string(reinterpret_cast<const char*>(Data), Size));
            (void)exifDatum.toFloat();
        }

        // Create ValueType with pair<int, int>
        std::pair<int, int> intPair(static_cast<int>(Size), static_cast<int>(Size) * -1);
        Exiv2::ValueType<std::pair<int, int>> intPairValue(
            reinterpret_cast<const Exiv2::byte*>(&intPair), 
            sizeof(intPair), 
            Exiv2::littleEndian
        );
        (void)intPairValue.toFloat();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}