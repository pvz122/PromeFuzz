// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::XmpTextValue::toUint32 at value.cpp:562:24 in value.hpp
// Exiv2::XmpTextValue::count at value.cpp:522:22 in value.hpp
// Exiv2::XmpTextValue::toRational at value.cpp:570:24 in value.hpp
// Exiv2::XmpTextValue::toInt64 at value.cpp:558:23 in value.hpp
// Exiv2::XmpTextValue::toFloat at value.cpp:566:21 in value.hpp
// Exiv2::XmpTextValue::size at value.cpp:518:22 in value.hpp
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpTextValue value;
        std::string str(reinterpret_cast<const char*>(Data), Size);
        value.read(str);

        // Test toUint32
        (void)value.toUint32();

        // Test count
        (void)value.count();

        // Test toRational
        (void)value.toRational();

        // Test toInt64
        (void)value.toInt64();

        // Test toFloat
        (void)value.toFloat();

        // Test size
        (void)value.size();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}