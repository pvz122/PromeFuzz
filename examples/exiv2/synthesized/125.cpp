// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpValue::setXmpStruct at value.cpp:424:16 in value.hpp
// Exiv2::XmpValue::xmpStruct at value.cpp:450:31 in value.hpp
// Exiv2::XmpValue::setXmpArrayType at value.cpp:420:16 in value.hpp
// Exiv2::XmpValue::xmpArrayType at value.cpp:428:34 in value.hpp
// Exiv2::XmpValue::read at value.cpp:463:15 in value.hpp
// Exiv2::XmpValue::copy at value.cpp:454:18 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_125(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create XmpTextValue object (concrete subclass of XmpValue)
        Exiv2::XmpTextValue xmpValue;

        // Test setXmpStruct
        xmpValue.setXmpStruct(static_cast<Exiv2::XmpValue::XmpStruct>(Data[0] % 2));

        // Test xmpStruct
        (void)xmpValue.xmpStruct();

        // Test setXmpArrayType
        xmpValue.setXmpArrayType(static_cast<Exiv2::XmpValue::XmpArrayType>(Data[0] % 4));

        // Test xmpArrayType
        (void)xmpValue.xmpArrayType();

        // Test read
        if (Size > 1) {
            xmpValue.read(Data + 1, Size - 1);
        }

        // Test copy
        if (Size > 1) {
            Exiv2::byte buf[1024];
            xmpValue.copy(buf);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}