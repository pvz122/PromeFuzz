// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <exiv2/value.hpp>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_679(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create DataValue
    Exiv2::DataValue dataValue(Data, Size);
    try {
        dataValue.toInt64();
        if (Size > 1) {
            dataValue.toInt64(Size % 10);
        }
    } catch (...) {}

    // Create ValueType<float>
    float floatVal = 3.14f;
    Exiv2::ValueType<float> floatValue(floatVal);
    try {
        floatValue.toInt64();
        if (Size > 1) {
            floatValue.toInt64(Size % 10);
        }
    } catch (...) {}

    // Create ValueType<int>
    int intVal = 42;
    Exiv2::ValueType<int> intValue(intVal);
    try {
        intValue.toInt64();
        if (Size > 1) {
            intValue.toInt64(Size % 10);
        }
    } catch (...) {}

    return 0;
}