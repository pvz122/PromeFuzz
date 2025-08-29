// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::Internal::ContainerStorage::unsafeAt at slice.hpp:284:29 in slice.hpp
// Exiv2::Internal::ContainerStorage::unsafeGetIteratorAt at slice.hpp:294:26 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include "value.hpp"
#include "slice.hpp"

extern "C" int LLVMFuzzerTestOneInput_686(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        // Create DataValue
        Exiv2::DataValue dataValue(Data, Size);
        dataValue.toInt64();
        if (Size > 1) dataValue.toInt64(Size % 2);

        // Create ValueType<float>
        Exiv2::ValueType<float> floatValue(Data, Size, Exiv2::littleEndian);
        floatValue.toInt64();
        if (Size > 1) floatValue.toInt64(Size % 2);

        // Create ContainerStorage
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::ContainerStorage storage(vec, 0, Size);
        if (Size > 0) {
            storage.unsafeAt(Size % vec.size());
            storage.unsafeGetIteratorAt(Size % vec.size());
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}