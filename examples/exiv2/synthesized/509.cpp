// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
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
#include <exiv2/value.hpp>
#include <exiv2/slice.hpp>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_509(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue
    Exiv2::DataValue dataValue(Exiv2::unsignedByte);
    try {
        dataValue.read(Data, Size);
        dataValue.toInt64(Size % (dataValue.size() + 1));
    } catch (...) {}

    // Initialize ValueType<float>
    float floatVal = static_cast<float>(Size);
    Exiv2::ValueType<float> valueTypeFloat(floatVal, Exiv2::tiffFloat);
    try {
        valueTypeFloat.toInt64(0);
    } catch (...) {}

    // Initialize ContainerStorage
    std::vector<uint8_t> vec(Data, Data + Size);
    Exiv2::Internal::ContainerStorage storage(vec, 0, Size);
    try {
        storage.unsafeAt(Size % (vec.size() + 1));
    } catch (...) {}

    try {
        storage.unsafeGetIteratorAt(Size % (vec.size() + 1));
    } catch (...) {}

    return 0;
}