// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_493(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy buffer with fuzzed data
        std::vector<Exiv2::byte> buffer(Data, Data + Size);

        // Initialize Value with fuzzed data (using unsignedLong type)
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
        value->read(buffer.data(), buffer.size(), Exiv2::littleEndian);

        // Call target functions
        (void)value->size();
        (void)value->toRational(0);
        (void)value->count();
        (void)value->toUint32(0);
        (void)value->toInt64(0);
        (void)value->toString(0);

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}