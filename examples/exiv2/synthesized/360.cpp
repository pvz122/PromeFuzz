// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::clone at value.hpp:265:13 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toFloat at value.cpp:164:18 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toFloat at value.cpp:164:18 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toString at value.cpp:147:24 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toString at value.cpp:147:24 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toRational at value.cpp:169:21 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_360(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue with random type
    Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[0] % (Exiv2::lastTypeId + 1));
    Exiv2::DataValue value(typeId);

    // Populate with remaining data
    if (Size > 1) {
        value.read(Data + 1, Size - 1);
    }

    // Test count()
    value.count();

    // Test clone()
    auto cloned = value.clone();

    // Test toFloat() with various indices
    if (value.count() > 0) {
        value.toFloat(0);
        if (value.count() > 1) {
            value.toFloat(1);
        }
    }

    // Test size()
    value.size();

    // Test toString() with various indices
    if (value.count() > 0) {
        value.toString(0);
        if (value.count() > 1) {
            value.toString(1);
        }
    }

    // Test toRational() with various indices
    if (value.count() > 0) {
        value.toRational(0);
        if (value.count() > 1) {
            value.toRational(1);
        }
    }

    return 0;
}