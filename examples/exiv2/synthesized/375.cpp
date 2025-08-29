// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::TimeValue::read at value.cpp:893:16 in value.hpp
// Exiv2::TimeValue::setTime at value.cpp:983:17 in value.hpp
// Exiv2::TimeValue::copy at value.cpp:987:19 in value.hpp
// Exiv2::TimeValue::toRational at value.cpp:1054:21 in value.hpp
// Exiv2::TimeValue::toUint32 at value.cpp:1046:21 in value.hpp
// Exiv2::TimeValue::toFloat at value.cpp:1050:18 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_375(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize TimeValue with some default values
        Exiv2::TimeValue timeValue(12, 30, 45, 2, 30);

        // Test read()
        if (Size > 0) {
            timeValue.read(Data, Size);
        }

        // Test setTime()
        Exiv2::TimeValue::Time time;
        time.hour = Data[0] % 24;
        timeValue.setTime(time);

        // Test copy()
        if (Size > 12) {
            Exiv2::byte buf[12];
            timeValue.copy(buf);
        }

        // Test toRational()
        timeValue.toRational();

        // Test toUint32()
        timeValue.toUint32();

        // Test toFloat()
        timeValue.toFloat();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}