// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
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
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_728(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue
    Exiv2::DataValue dataValue(Exiv2::unsignedByte);
    dataValue.read(Data, Size);
    try {
        dataValue.toInt64(0);
        dataValue.toInt64(Size % 10);
    } catch (...) {}

    // Initialize ValueType<float>
    Exiv2::ValueType<float> floatValue;
    try {
        floatValue.toInt64(0);
        floatValue.toInt64(Size % 10);
    } catch (...) {}

    // Initialize ValueType<int>
    Exiv2::ValueType<int> intValue;
    try {
        intValue.toInt64(0);
        intValue.toInt64(Size % 10);
    } catch (...) {}

    // Initialize ContainerStorage
    std::vector<int> vec;
    for (size_t i = 0; i < Size && i < 10; ++i) {
        vec.push_back(Data[i]);
    }
    Exiv2::Internal::ContainerStorage storage(vec, 0, vec.size());
    try {
        storage.unsafeAt(Size % vec.size());
    } catch (...) {}

    try {
        storage.unsafeGetIteratorAt(Size % vec.size());
    } catch (...) {}

    return 0;
}