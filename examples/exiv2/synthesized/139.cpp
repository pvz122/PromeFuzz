// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getValue at value.hpp:1360:14 in value.hpp
// Exiv2::getFloat at types.cpp:296:7 in types.hpp
// Exiv2::toData at value.hpp:1436:15 in value.hpp
// Exiv2::us2Data at types.cpp:331:8 in types.hpp
// Exiv2::f2Data at types.cpp:410:8 in types.hpp
// Exiv2::ull2Data at types.cpp:357:8 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // Need at least 8 bytes for meaningful fuzzing

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Test getValue<float>
    if (Size >= 4) {
        try {
            float val = Exiv2::getValue<float>(Data, byteOrder);
            (void)val; // Avoid unused variable warning
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test getFloat
    if (Size >= 4) {
        try {
            float val = Exiv2::getFloat(Data, byteOrder);
            (void)val;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test toData<float>
    if (Size >= 4) {
        try {
            Exiv2::byte buf[4];
            float f = 0.0f;
            std::memcpy(&f, Data, sizeof(f));
            size_t written = Exiv2::toData(buf, f, byteOrder);
            (void)written;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test us2Data
    if (Size >= 2) {
        try {
            Exiv2::byte buf[2];
            uint16_t s = 0;
            std::memcpy(&s, Data, sizeof(s));
            size_t written = Exiv2::us2Data(buf, s, byteOrder);
            (void)written;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test f2Data
    if (Size >= 4) {
        try {
            Exiv2::byte buf[4];
            float f = 0.0f;
            std::memcpy(&f, Data, sizeof(f));
            size_t written = Exiv2::f2Data(buf, f, byteOrder);
            (void)written;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test ull2Data
    if (Size >= 8) {
        try {
            Exiv2::byte buf[8];
            uint64_t l = 0;
            std::memcpy(&l, Data, sizeof(l));
            size_t written = Exiv2::ull2Data(buf, l, byteOrder);
            (void)written;
        } catch (...) {
            // Ignore exceptions
        }
    }

    return 0;
}