// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::Internal::ContainerStorage::unsafeAt at slice.hpp:284:29 in slice.hpp
// Exiv2::Internal::ContainerStorage::unsafeAt at slice.hpp:284:29 in slice.hpp
// Exiv2::Internal::ContainerStorage::unsafeGetIteratorAt at slice.hpp:294:26 in slice.hpp
// Exiv2::Internal::ContainerStorage::unsafeGetIteratorAt at slice.hpp:294:26 in slice.hpp
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
#include <exiv2/slice.hpp>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_506(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create DataValue
    Exiv2::DataValue dataValue(Data, Size);
    try {
        dataValue.toInt64(0);
        dataValue.toInt64(Size / 2);
    } catch (...) {}

    // Create ValueType<float>
    float floatVal = 3.14f;
    Exiv2::ValueType<float> valueTypeFloat(floatVal);
    try {
        valueTypeFloat.toInt64(0);
    } catch (...) {}

    // Create ValueType<int>
    int intVal = 42;
    Exiv2::ValueType<int> valueTypeInt(intVal);
    try {
        valueTypeInt.toInt64(0);
    } catch (...) {}

    // Create ContainerStorage
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Exiv2::Internal::ContainerStorage containerStorage(vec, 0, vec.size());
    try {
        containerStorage.unsafeAt(0);
        containerStorage.unsafeAt(Size % vec.size());
    } catch (...) {}

    try {
        containerStorage.unsafeGetIteratorAt(0);
        containerStorage.unsafeGetIteratorAt(Size % vec.size());
    } catch (...) {}

    return 0;
}