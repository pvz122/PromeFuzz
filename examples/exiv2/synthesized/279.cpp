// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1097:15 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::Internal::ContainerStorage::unsafeAt at slice.hpp:284:29 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_279(const uint8_t *Data, size_t Size) {
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
    float floatVal = Size > 0 ? static_cast<float>(Data[0]) : 0.0f;
    Exiv2::ValueType<float> floatValue(floatVal);
    try {
        floatValue.toInt64();
    } catch (...) {}

    // Skip ValueType<int64_t> since it causes linking errors
    // Instead use ValueType<short> which is supported
    short shortVal = Size > 0 ? static_cast<short>(Data[0]) : 0;
    Exiv2::ValueType<short> shortValue(shortVal);
    try {
        shortValue.toInt64();
    } catch (...) {}

    // Test ContainerStorage
    std::vector<uint8_t> containerData(Data, Data + Size);
    Exiv2::Internal::ContainerStorage containerStorage(containerData, 0, containerData.size());
    try {
        if (!containerData.empty()) {
            containerStorage.unsafeAt(Size % containerData.size());
            containerStorage.unsafeGetIteratorAt(Size % containerData.size());
        }
    } catch (...) {}

    return 0;
}