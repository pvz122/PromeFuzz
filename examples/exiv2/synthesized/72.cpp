// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::StringValueBase::read at value.cpp:178:22 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:260:16 in exif.hpp
// Exiv2::AsciiValue::read at value.cpp:245:17 in value.hpp
// Exiv2::CommentValue::read at value.cpp:305:19 in value.hpp
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
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test Exiv2::XmpTextValue::read
    try {
        Exiv2::XmpTextValue xmpTextValue;
        xmpTextValue.read(input);
    } catch (...) {}

    // Test Exiv2::ValueType::read
    try {
        Exiv2::ValueType<int> valueType;
        valueType.read(input);
    } catch (...) {}

    // Test Exiv2::StringValueBase::read
    try {
        Exiv2::StringValue stringValue;
        stringValue.read(input);
    } catch (...) {}

    // Test Exiv2::Exifdatum::setValue
    try {
        Exiv2::ExifKey key("Exif.Image.Make");
        Exiv2::Exifdatum exifDatum(key);
        exifDatum.setValue(input);
    } catch (...) {}

    // Test Exiv2::AsciiValue::read
    try {
        Exiv2::AsciiValue asciiValue;
        asciiValue.read(input);
    } catch (...) {}

    // Test Exiv2::CommentValue::read
    try {
        Exiv2::CommentValue commentValue;
        commentValue.read(input);
    } catch (...) {}

    return 0;
}