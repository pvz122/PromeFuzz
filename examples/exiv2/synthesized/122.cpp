// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::TimeValue::toInt64 at value.cpp:1034:20 in value.hpp
// Exiv2::TimeValue::count at value.cpp:1008:19 in value.hpp
// Exiv2::TimeValue::clone at value.hpp:1032:13 in value.hpp
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
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    Exiv2::TimeValue timeValue;

    // Test toInt64
    (void)timeValue.toInt64();

    // Test count
    (void)timeValue.count();

    // Test clone
    auto cloned = timeValue.clone();
    (void)cloned.get();

    // Test toRational
    (void)timeValue.toRational();

    // Test toUint32
    (void)timeValue.toUint32();

    // Test toFloat
    (void)timeValue.toFloat();

    return 0;
}