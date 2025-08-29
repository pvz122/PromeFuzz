// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType::size at value.hpp:1541:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType::count at value.hpp:1536:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toInt64 at value.hpp:1611:38 in value.hpp
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
#include <vector>
#include <string>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        // Create a buffer with fuzzed data
        std::vector<Exiv2::byte> buf(Data, Data + Size);

        // Initialize ValueType with fuzzed data
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> value(
            buf.data(), 
            buf.size(), 
            Exiv2::littleEndian
        );

        // Call size()
        value.size();

        // Call toRational() with various indices
        for (size_t i = 0; i < 2; ++i) {
            try {
                value.toRational(i);
            } catch (...) {}
        }

        // Call count()
        value.count();

        // Call toUint32() with various indices
        for (size_t i = 0; i < 2; ++i) {
            try {
                value.toUint32(i);
            } catch (...) {}
        }

        // Call toInt64() with various indices
        for (size_t i = 0; i < 2; ++i) {
            try {
                value.toInt64(i);
            } catch (...) {}
        }

        // Call toString() with various indices
        for (size_t i = 0; i < 2; ++i) {
            try {
                value.toString(i);
            } catch (...) {}
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}