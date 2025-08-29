// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::read at value.cpp:183:22 in value.hpp
// Exiv2::StringValueBase::size at value.cpp:201:25 in value.hpp
// Exiv2::StringValueBase::count at value.cpp:197:25 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::toInt64 at value.cpp:209:26 in value.hpp
// Exiv2::StringValueBase::toUint32 at value.cpp:214:27 in value.hpp
// Exiv2::StringValueBase::copy at value.cpp:190:25 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_160(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a StringValueBase-derived object (using StringValue)
        Exiv2::StringValue value;

        // Test read()
        value.read(Data, Size);

        // Test size() and count()
        (void)value.size();
        (void)value.count();

        // Test toInt64() and toUint32()
        if (Size > 1) {
            size_t n = Data[0] % (Size - 1);
            (void)value.toInt64(n);
            (void)value.toUint32(n);
        } else {
            (void)value.toInt64();
            (void)value.toUint32();
        }

        // Test copy()
        if (Size > 0) {
            Exiv2::byte* buf = new Exiv2::byte[Size];
            value.copy(buf);
            delete[] buf;
        }
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}