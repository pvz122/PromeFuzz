// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toUint32 at value.cpp:159:21 in value.hpp
// Exiv2::DataValue::toString at value.cpp:147:24 in value.hpp
// Exiv2::DataValue::toRational at value.cpp:169:21 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toInt64 at value.cpp:154:20 in value.hpp
// Exiv2::DataValue::toUint32 at value.cpp:159:21 in value.hpp
// Exiv2::DataValue::toString at value.cpp:147:24 in value.hpp
// Exiv2::DataValue::toRational at value.cpp:169:21 in value.hpp
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
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_79(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue with random type
    Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[0] % (Exiv2::lastTypeId + 1));
    Exiv2::DataValue value(typeId);

    // Populate DataValue with remaining input data
    if (Size > 1) {
        value.read(Data + 1, Size - 1);
    }

    // Call target functions
    (void)value.count();
    (void)value.size();

    if (value.count() > 0) {
        try {
            (void)value.toInt64();
            (void)value.toUint32();
            (void)value.toString(0);
            (void)value.toRational();
        } catch (...) {
            // Ignore exceptions from invalid operations
        }
    }

    // Try with some indices (ensure they're within bounds)
    if (value.count() > 0) {
        size_t idx = Data[0] % value.count();  // Ensure idx is within bounds
        try {
            (void)value.toInt64(idx);
            (void)value.toUint32(idx);
            (void)value.toString(idx);
            (void)value.toRational(idx);
        } catch (...) {
            // Ignore exceptions from invalid operations
        }
    }

    return 0;
}