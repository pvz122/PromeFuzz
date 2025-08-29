// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::ValueType::toString at value.hpp:1563:27 in value.hpp
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
#include <cstddef>
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_740(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a ValueType instance with a specific type
        Exiv2::ValueType<int> valueType;

        // Call size()
        (void)valueType.size();

        // Call toRational() with a bounded index
        size_t n_rational = Data[0] % 16;
        (void)valueType.toRational(n_rational);

        // Call count()
        (void)valueType.count();

        // Call toUint32() with a bounded index
        size_t n_uint32 = Data[0] % 16;
        (void)valueType.toUint32(n_uint32);

        // Call toInt64() with a bounded index
        size_t n_int64 = Data[0] % 16;
        (void)valueType.toInt64(n_int64);

        // Call toString() with a bounded index
        size_t n_string = Data[0] % 16;
        (void)valueType.toString(n_string);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}