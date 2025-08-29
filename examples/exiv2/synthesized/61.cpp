// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::copy at value.cpp:124:19 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toFloat at value.cpp:164:18 in value.hpp
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toRational at value.cpp:169:21 in value.hpp
// Exiv2::DataValue::count at value.cpp:100:19 in value.hpp
// Exiv2::DataValue::toUint32 at value.cpp:159:21 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize DataValue with random type
    Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[0] % (Exiv2::lastTypeId + 1));
    Exiv2::DataValue value(typeId);

    // Populate the DataValue with remaining input data
    if (Size > 1) {
        value.read(Data + 1, Size - 1);
    }

    // Test count() function
    (void)value.count();

    // Test copy() function
    if (value.size() > 0) {
        Exiv2::byte* buf = new Exiv2::byte[value.size()];
        (void)value.copy(buf);
        delete[] buf;
    }

    // Test toFloat() function
    if (value.count() > 0) {
        (void)value.toFloat();
    }

    // Test size() function
    (void)value.size();

    // Test toRational() function
    if (value.count() > 0) {
        (void)value.toRational();
    }

    // Test toUint32() function
    if (value.count() > 0) {
        (void)value.toUint32();
    }

    return 0;
}