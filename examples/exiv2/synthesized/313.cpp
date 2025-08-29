// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::Exifdatum::toInt64 at exif.cpp:344:20 in exif.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::LangAltValue::toInt64 at value.cpp:721:23 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_313(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Initialize Exiv2 objects
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (!image) return 0;
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) return 0;

        // Fuzz Exifdatum::toInt64
        for (auto& exifDatum : exifData) {
            exifDatum.toInt64(Data[0] % 10);
        }

        // Fuzz ValueType<float>::toInt64
        float floatVal = *reinterpret_cast<const float*>(Data);
        Exiv2::Value::UniquePtr floatValue = Exiv2::Value::create(Exiv2::tiffFloat);
        floatValue->read(reinterpret_cast<const uint8_t*>(&floatVal), sizeof(floatVal), Exiv2::invalidByteOrder);
        floatValue->toInt64(Data[0] % 10);

        // Fuzz ValueType<double>::toInt64
        double doubleVal = *reinterpret_cast<const double*>(Data);
        Exiv2::Value::UniquePtr doubleValue = Exiv2::Value::create(Exiv2::tiffDouble);
        doubleValue->read(reinterpret_cast<const uint8_t*>(&doubleVal), sizeof(doubleVal), Exiv2::invalidByteOrder);
        doubleValue->toInt64(Data[0] % 10);

        // Fuzz LangAltValue::toInt64
        Exiv2::LangAltValue langAltValue;
        langAltValue.toInt64(Data[0] % 10);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}