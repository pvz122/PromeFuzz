// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::Exifdatum::typeId at exif.cpp:316:19 in exif.hpp
// Exiv2::IptcData::empty at iptc.hpp:247:22 in iptc.hpp
// Exiv2::IptcData::end at iptc.hpp:211:12 in iptc.hpp
// Exiv2::Iptcdatum::typeId at iptc.cpp:112:19 in iptc.hpp
// Exiv2::XmpData::empty at xmp.cpp:464:15 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::typeId at xmp.cpp:336:18 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::typeId at value.hpp:85:10 in value.hpp
// Exiv2::TypeInfo::typeName at types.cpp:71:23 in types.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_294(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    // Create a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Open the dummy file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) return 0;

        image->readMetadata();

        // Test Exifdatum::typeId
        Exiv2::ExifData &exifData = image->exifData();
        if (!exifData.empty()) {
            for (auto &datum : exifData) {
                (void)datum.typeId();
            }
        }

        // Test Iptcdatum::typeId
        Exiv2::IptcData &iptcData = image->iptcData();
        if (!iptcData.empty()) {
            for (auto &datum : iptcData) {
                (void)datum.typeId();
            }
        }

        // Test Xmpdatum::typeId
        Exiv2::XmpData &xmpData = image->xmpData();
        if (!xmpData.empty()) {
            for (auto &datum : xmpData) {
                (void)datum.typeId();
            }
        }

        // Test Value::create and Value::typeId
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));
        if (value.get() != nullptr) {
            (void)value->typeId();
        }

        // Test TypeInfo::typeName
        (void)Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}