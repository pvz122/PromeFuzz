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
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_581(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create DataValue
    Exiv2::DataValue dataValue(Data, Size);
    try {
        dataValue.toInt64(0);
        dataValue.toInt64(Size / 2);
    } catch (...) {}

    // Create ValueType<float>
    float floatVal = 0.0f;
    if (Size >= sizeof(float)) {
        memcpy(&floatVal, Data, sizeof(float));
    }
    Exiv2::ValueType<float> floatValueType(floatVal);
    try {
        floatValueType.toInt64(0);
    } catch (...) {}

    // Create ValueType<int>
    int intVal = 0;
    if (Size >= sizeof(int)) {
        memcpy(&intVal, Data, sizeof(int));
    }
    Exiv2::ValueType<int> intValueType(intVal);
    try {
        intValueType.toInt64(0);
    } catch (...) {}

    // Create ContainerStorage
    std::vector<uint8_t> containerData(Data, Data + Size);
    Exiv2::Internal::ContainerStorage containerStorage(containerData, 0, Size);
    try {
        containerStorage.unsafeAt(0);
        containerStorage.unsafeAt(Size / 2);
    } catch (...) {}

    try {
        containerStorage.unsafeGetIteratorAt(0);
        containerStorage.unsafeGetIteratorAt(Size / 2);
    } catch (...) {}

    return 0;
}