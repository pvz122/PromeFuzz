// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:254:17 in exif.hpp
// Exiv2::Exifdatum::toInt64 at exif.cpp:344:20 in exif.hpp
// Exiv2::TimeValue::toInt64 at value.cpp:1034:20 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <fstream>
#include <cstdint>
#include <cstdlib>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_562(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    // Test Exiv2::Exifdatum::toInt64
    try {
        Exiv2::ExifKey key("Exif.Image.ImageWidth");
        Exiv2::Exifdatum datum(key);
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedLong);
        if (Size >= sizeof(uint32_t)) {
            value->read(Data, sizeof(uint32_t), Exiv2::littleEndian);
            datum.setValue(value.get());
            (void)datum.toInt64();
        }
    } catch (...) {}

    // Test Exiv2::TimeValue::toInt64
    try {
        Exiv2::TimeValue timeValue;
        (void)timeValue.toInt64();
    } catch (...) {}

    // Test ValueType with supported types
    try {
        if (Size >= sizeof(int)) {
            int val = *reinterpret_cast<const int*>(Data);
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::signedLong);
            value->read(Data, sizeof(int), Exiv2::littleEndian);
            (void)value->toInt64();
        }
    } catch (...) {}

    try {
        if (Size >= sizeof(float)) {
            float val = *reinterpret_cast<const float*>(Data);
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::tiffFloat);
            value->read(Data, sizeof(float), Exiv2::littleEndian);
            (void)value->toInt64();
        }
    } catch (...) {}

    try {
        if (Size >= sizeof(double)) {
            double val = *reinterpret_cast<const double*>(Data);
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::tiffDouble);
            value->read(Data, sizeof(double), Exiv2::littleEndian);
            (void)value->toInt64();
        }
    } catch (...) {}

    return 0;
}