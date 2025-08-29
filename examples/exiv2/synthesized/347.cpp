// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::TimeValue::read at value.cpp:898:16 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1512:19 in value.hpp
// Exiv2::AsciiValue::read at value.cpp:245:17 in value.hpp
// Exiv2::CommentValue::read at value.cpp:305:19 in value.hpp
// Exiv2::DataValue::read at value.cpp:110:16 in value.hpp
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
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_347(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::string input(reinterpret_cast<const char*>(Data), Size);

        // Test Exiv2::TimeValue::read with try-catch
        {
            Exiv2::TimeValue timeValue;
            try {
                timeValue.read(input);
            } catch (...) {}
        }

        // Test Exiv2::ValueType::read with try-catch
        {
            try {
                Exiv2::ValueType<int> intValue(0);
                intValue.read(input);
            } catch (...) {}

            try {
                Exiv2::ValueType<float> floatValue(0.0f);
                floatValue.read(input);
            } catch (...) {}
        }

        // Test Exiv2::AsciiValue::read with try-catch
        {
            try {
                Exiv2::AsciiValue asciiValue("");
                asciiValue.read(input);
            } catch (...) {}
        }

        // Test Exiv2::CommentValue::read with try-catch
        {
            try {
                Exiv2::CommentValue commentValue;
                commentValue.read(input);
            } catch (...) {}
        }

        // Test Exiv2::DataValue::read with try-catch
        {
            try {
                Exiv2::DataValue dataValue;
                dataValue.read(input);
            } catch (...) {}
        }
    } catch (...) {}

    return 0;
}