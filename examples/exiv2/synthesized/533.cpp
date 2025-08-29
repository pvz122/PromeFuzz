// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
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
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_533(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::DataValue::toInt64
    try {
        Exiv2::DataValue dataValue(Exiv2::unsignedLong);
        dataValue.read(Data, Size, Exiv2::littleEndian);
        dataValue.toInt64();
        if (Size > 1) {
            dataValue.toInt64(Size % dataValue.count());
        }
    } catch (...) {}

    // Test Exiv2::ValueType<float>::toInt64
    try {
        Exiv2::ValueType<float> floatValue;
        floatValue.read(Data, Size, Exiv2::littleEndian);
        floatValue.toInt64();
        if (Size > 1) {
            floatValue.toInt64(Size % floatValue.count());
        }
    } catch (...) {}

    // Test Exiv2::ValueType::toInt64 (template)
    try {
        Exiv2::ValueType<int> intValue;
        intValue.read(Data, Size, Exiv2::littleEndian);
        intValue.toInt64();
        if (Size > 1) {
            intValue.toInt64(Size % intValue.count());
        }
    } catch (...) {}

    // Test Exiv2::Internal::ContainerStorage::unsafeAt
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::ContainerStorage storage(vec, 0, Size);
        if (Size > 0) {
            storage.unsafeAt(Size % vec.size());
        }
    } catch (...) {}

    // Test Exiv2::Internal::ContainerStorage::unsafeGetIteratorAt
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::ContainerStorage storage(vec, 0, Size);
        if (Size > 0) {
            storage.unsafeGetIteratorAt(Size % vec.size());
        }
    } catch (...) {}

    return 0;
}