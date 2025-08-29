// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::CommentValue::write at value.cpp:357:29 in value.hpp
// Exiv2::DateValue::write at value.cpp:843:26 in value.hpp
// Exiv2::ValueType::write at value.hpp:1551:29 in value.hpp
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
#include <exiv2/iptc.hpp>
#include <fstream>
#include <sstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_721(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string dummy(reinterpret_cast<const char*>(Data), Size);
        std::stringstream ss;

        // Test Exiv2::LangAltValue::write
        Exiv2::LangAltValue langAltValue(dummy);
        langAltValue.write(ss);

        // Test Exiv2::AsciiValue::write
        Exiv2::AsciiValue asciiValue;
        asciiValue.write(ss);

        // Test Exiv2::CommentValue::write
        Exiv2::CommentValue commentValue;
        commentValue.write(ss);

        // Test Exiv2::DateValue::write
        Exiv2::DateValue dateValue;
        dateValue.write(ss);

        // Test Exiv2::ValueType::write with explicit type
        Exiv2::ByteOrder byteOrder = Exiv2::littleEndian;
        Exiv2::ValueType<unsigned short> valueType(reinterpret_cast<const Exiv2::byte*>(Data), Size, byteOrder, Exiv2::unsignedShort);
        valueType.write(ss);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}