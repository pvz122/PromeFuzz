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
#include <exiv2/value.hpp>
#include <exiv2/slice.hpp>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_698(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        // Create DataValue
        Exiv2::DataValue dataValue(Data, Size);
        dataValue.toInt64();
        if (Size > 1) dataValue.toInt64(Size % 2);

        // Create ValueType<float>
        std::vector<float> floatVec;
        for (size_t i = 0; i < Size / sizeof(float) && i < 10; ++i) {
            float val;
            memcpy(&val, Data + i * sizeof(float), sizeof(float));
            floatVec.push_back(val);
        }
        if (!floatVec.empty()) {
            Exiv2::ValueType<float> floatValue(reinterpret_cast<const Exiv2::byte*>(floatVec.data()), 
                                              floatVec.size() * sizeof(float), 
                                              Exiv2::littleEndian);
            floatValue.toInt64();
            if (floatVec.size() > 1) floatValue.toInt64(Size % floatVec.size());
        }

        // Skip ValueType<int64_t> since it causes linking errors
        // Test ContainerStorage with float vector instead
        if (!floatVec.empty()) {
            Exiv2::Internal::ContainerStorage storage(floatVec, 0, floatVec.size());
            if (!floatVec.empty()) {
                try {
                    storage.unsafeAt(Size % floatVec.size());
                    storage.unsafeGetIteratorAt(Size % floatVec.size());
                } catch (...) {
                    // Ignore out of bounds exceptions
                }
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}