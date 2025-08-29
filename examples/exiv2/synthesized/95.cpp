// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue
    Exiv2::DataValue dataValue(Exiv2::unsignedByte);
    try {
        dataValue.toInt64(Size % 10);
    } catch (...) {}

    // Initialize PtrSliceStorage
    std::vector<uint8_t> vec(Data, Data + Size);
    Exiv2::Internal::PtrSliceStorage ptrSlice(vec.data(), 0, Size);
    try {
        if (Size > 0) {
            ptrSlice.unsafeAt(Size % Size);
            ptrSlice.unsafeGetIteratorAt(Size % Size);
        }
    } catch (...) {}

    // Initialize ContainerStorage
    Exiv2::Internal::ContainerStorage containerStorage(vec, 0, Size);
    try {
        if (Size > 0) {
            containerStorage.unsafeAt(Size % Size);
            containerStorage.unsafeGetIteratorAt(Size % Size);
        }
    } catch (...) {}

    return 0;
}