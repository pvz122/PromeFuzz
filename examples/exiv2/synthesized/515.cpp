// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
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
#include <cstdint>
#include <vector>
#include <memory>
#include "exiv2/value.hpp"
#include "exiv2/slice.hpp"
#include "exiv2/datasets.hpp"

extern "C" int LLVMFuzzerTestOneInput_515(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create DataValue
    try {
        Exiv2::DataValue dataValue(Data, Size);
        dataValue.toInt64();
        if (Size > 1) {
            dataValue.toInt64(Size % 10);
        }
    } catch (...) {}

    // Create ValueType<float>
    try {
        float floatVal = 3.14f;
        Exiv2::ValueType<float> floatValue(floatVal);
        floatValue.toInt64();
        if (Size > 1) {
            floatValue.toInt64(Size % 10);
        }
    } catch (...) {}

    // Test ContainerStorage
    try {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        Exiv2::Internal::ContainerStorage storage(vec, 0, vec.size());
        if (Size > 1) {
            storage.unsafeAt(Size % vec.size());
            storage.unsafeGetIteratorAt(Size % vec.size());
        }
    } catch (...) {}

    return 0;
}