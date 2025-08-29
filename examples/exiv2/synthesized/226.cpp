// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpArrayValue::read at value.cpp:582:20 in value.hpp
// Exiv2::XmpArrayValue::toFloat at value.cpp:617:22 in value.hpp
// Exiv2::StringValueBase::toFloat at value.cpp:219:24 in value.hpp
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
#include <exiv2/types.hpp>
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_226(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::XmpArrayValue::toFloat
        {
            Exiv2::XmpArrayValue xmpVal(Exiv2::xmpBag);
            if (Size > 1) {
                xmpVal.read(std::string(reinterpret_cast<const char*>(Data), Size));
                (void)xmpVal.toFloat();
            }
        }

        // Test Exiv2::AsciiValue::toFloat
        {
            if (Size > 1) {
                Exiv2::AsciiValue asciiVal(std::string(reinterpret_cast<const char*>(Data), Size));
                (void)asciiVal.toFloat();
            }
        }

        // Test Exiv2::DateValue::toFloat
        {
            Exiv2::DateValue dateVal(2023, 10, 5);
            (void)dateVal.toFloat();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}