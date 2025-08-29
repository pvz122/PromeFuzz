// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::StringValueBase::toRational at value.cpp:224:27 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::Value::toString at value.cpp:81:20 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_479(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a concrete ValueType instance (e.g., StringValue)
        Exiv2::StringValue valueType;

        // Call size()
        valueType.size();

        // Call toRational() with a bounded index
        size_t n_rational = Data[0] % 16;
        valueType.toRational(n_rational);

        // Call count()
        valueType.count();

        // Call toUint32() with a bounded index
        size_t n_uint32 = Data[0] % 16;
        valueType.toUint32(n_uint32);

        // Call toInt64() with a bounded index
        size_t n_int64 = Data[0] % 16;
        valueType.toInt64(n_int64);

        // Call toString() with a bounded index
        size_t n_string = Data[0] % 16;
        valueType.toString(n_string);

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}