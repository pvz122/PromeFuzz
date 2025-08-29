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
#include <cstdint>
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_587(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    try {
        // Create a buffer with fuzzed data
        std::vector<Exiv2::byte> buffer(Data, Data + Size);
        Exiv2::ByteOrder byteOrder = Exiv2::littleEndian;

        // Test with different TypeIds
        const Exiv2::TypeId typeIds[] = {
            Exiv2::unsignedByte,
            Exiv2::asciiString,
            Exiv2::unsignedShort,
            Exiv2::unsignedLong,
            Exiv2::unsignedRational,
            Exiv2::signedByte,
            Exiv2::undefined,
            Exiv2::signedShort,
            Exiv2::signedLong,
            Exiv2::signedRational,
            Exiv2::tiffFloat,
            Exiv2::tiffDouble,
            Exiv2::string,
            Exiv2::xmpText
        };

        for (auto typeId : typeIds) {
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(typeId);
            if (!value) continue;

            value->read(buffer.data(), Size, byteOrder);

            // Call target API functions
            value->size();
            if (value->count() > 0) {
                value->toRational(0);
                value->toUint32(0);
                value->toInt64(0);
                value->toString(0);
            }
            value->count();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}