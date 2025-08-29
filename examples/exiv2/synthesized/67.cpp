// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::LangAltValue::toString at value.cpp:708:27 in value.hpp
// Exiv2::LangAltValue::toString at value.cpp:712:27 in value.hpp
// Exiv2::LangAltValue::write at value.cpp:687:29 in value.hpp
// Exiv2::LangAltValue::toInt64 at value.cpp:721:23 in value.hpp
// Exiv2::LangAltValue::read at value.cpp:636:19 in value.hpp
// Exiv2::LangAltValue::count at value.cpp:683:22 in value.hpp
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
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string input(reinterpret_cast<const char*>(Data), Size);
        Exiv2::LangAltValue value(input);

        // Test toString overloads
        value.toString(0);
        value.toString("x-default");

        // Test write
        std::ostringstream os;
        value.write(os);

        // Test toInt64
        value.toInt64();

        // Test read
        value.read(input);

        // Test count
        value.count();
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}