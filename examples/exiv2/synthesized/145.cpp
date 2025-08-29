// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::count at value.cpp:592:23 in value.hpp
// Exiv2::XmpArrayValue::toFloat at value.cpp:617:22 in value.hpp
// Exiv2::XmpArrayValue::toUint32 at value.cpp:613:25 in value.hpp
// Exiv2::XmpArrayValue::toString at value.cpp:604:28 in value.hpp
// Exiv2::XmpArrayValue::toRational at value.cpp:621:25 in value.hpp
// Exiv2::XmpArrayValue::toInt64 at value.cpp:609:24 in value.hpp
// Exiv2::XmpArrayValue::count at value.cpp:592:23 in value.hpp
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize XmpArrayValue with default type (xmpBag)
        Exiv2::XmpArrayValue xmpArrayValue;

        // Add some dummy data to the array
        xmpArrayValue.read("1.23");
        xmpArrayValue.read("42");
        xmpArrayValue.read("test");
        xmpArrayValue.read("3/4");
        xmpArrayValue.read("-123456789");

        // Get count of elements
        size_t count = xmpArrayValue.count();
        if (count == 0) return 0;

        // Use first byte to determine which function to test
        uint8_t selector = Data[0] % 6;
        size_t index = (Data[0] % count); // Ensure index is within bounds

        switch (selector) {
            case 0:
                (void)xmpArrayValue.toFloat(index);
                break;
            case 1:
                (void)xmpArrayValue.toUint32(index);
                break;
            case 2:
                (void)xmpArrayValue.toString(index);
                break;
            case 3:
                (void)xmpArrayValue.toRational(index);
                break;
            case 4:
                (void)xmpArrayValue.toInt64(index);
                break;
            case 5:
                (void)xmpArrayValue.count();
                break;
        }

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}