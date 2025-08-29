// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::toString at value.cpp:81:20 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::toString at value.cpp:81:20 in value.hpp
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
#include <exiv2/exiv2.hpp>
#include <cstdint>
#include <vector>
#include <utility>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_580(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize Exiv2
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);

        // Test with unsignedByte type
        std::unique_ptr<Exiv2::Value> val1(Exiv2::Value::create(Exiv2::unsignedByte));
        val1->read(Data, Size, Exiv2::littleEndian);
        val1->size();
        val1->count();
        if (val1->count() > 0) {
            val1->toRational(0);
            val1->toUint32(0);
            val1->toInt64(0);
            val1->toString(0);
        }

        // Test with unsignedShort type
        if (Size >= 2) {
            std::unique_ptr<Exiv2::Value> val2(Exiv2::Value::create(Exiv2::unsignedShort));
            val2->read(Data, 2, Exiv2::littleEndian);
            val2->size();
            val2->count();
            if (val2->count() > 0) {
                val2->toRational(0);
                val2->toUint32(0);
                val2->toInt64(0);
                val2->toString(0);
            }
        }

        // Test with unsignedRational type
        if (Size >= 8) {
            std::unique_ptr<Exiv2::Value> val3(Exiv2::Value::create(Exiv2::unsignedRational));
            val3->read(Data, 8, Exiv2::littleEndian);
            val3->size();
            val3->count();
            if (val3->count() > 0) {
                val3->toRational(0);
                val3->toUint32(0);
                val3->toInt64(0);
                val3->toString(0);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}