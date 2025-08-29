// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::Internal::ContainerStorage::unsafeAt at slice.hpp:284:29 in slice.hpp
// Exiv2::Internal::ContainerStorage::unsafeGetIteratorAt at slice.hpp:294:26 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <exiv2/value.hpp>
#include <exiv2/slice.hpp>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_640(const uint8_t *Data, size_t Size) {
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
    Exiv2::ValueType<float> floatValue;
    floatValue.read(reinterpret_cast<const Exiv2::byte*>(&floatVal), sizeof(float), Exiv2::littleEndian);
    try {
        floatValue.toInt64();
    } catch (...) {}

    // Test ContainerStorage
    std::vector<uint8_t> vec(Data, Data + Size);
    Exiv2::Internal::ContainerStorage storage(vec, 0, Size);
    try {
        if (Size > 0) {
            storage.unsafeAt(Size % vec.size());
        }
    } catch (...) {}

    try {
        if (Size > 0) {
            storage.unsafeGetIteratorAt(Size % vec.size());
        }
    } catch (...) {}

    return 0;
}