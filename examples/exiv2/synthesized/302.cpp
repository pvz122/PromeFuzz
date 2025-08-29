// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Exifdatum::setValue at exif.cpp:254:17 in exif.hpp
// Exiv2::Exifdatum::copy at exif.cpp:312:19 in exif.hpp
// Exiv2::ExifParser::encode at exif.hpp:560:15 in exif.hpp
// Exiv2::Image::byteOrder at image.cpp:681:18 in image.hpp
// Exiv2::Image::setByteOrder at image.cpp:677:13 in image.hpp
// Exiv2::ExifParser::decode at exif.cpp:490:23 in exif.hpp
// Exiv2::TiffParser::encode at tiffimage.cpp:219:25 in tiffimage.hpp
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
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_302(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Exiv2
    Exiv2::XmpParser::initialize();
    ::atexit(Exiv2::XmpParser::terminate);

    try {
        // Test Exifdatum::copy
        {
            Exiv2::ExifKey key("Exif.Image.Orientation");
            Exiv2::Exifdatum datum(key);
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::unsignedShort);
            value->read("1");
            datum.setValue(value.get());
            Exiv2::byte buf[1024];
            Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
            datum.copy(buf, byteOrder);
        }

        // Test ExifParser::encode
        {
            Exiv2::ExifData exifData;
            Exiv2::Blob blob;
            Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
            Exiv2::ExifParser::encode(blob, byteOrder, exifData);
        }

        // Test Image::byteOrder and setByteOrder
        {
            Exiv2::BasicIo::UniquePtr memIo(new Exiv2::MemIo);
            Exiv2::TiffImage tiffImage(std::move(memIo), true);
            Exiv2::ByteOrder byteOrder = tiffImage.byteOrder();
            tiffImage.setByteOrder(Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian);
        }

        // Test ExifParser::decode
        {
            Exiv2::ExifData exifData;
            if (Size > 0) {
                Exiv2::ExifParser::decode(exifData, Data, Size);
            }
        }

        // Test TiffParser::encode
        {
            Exiv2::BasicIo::UniquePtr memIo(new Exiv2::MemIo);
            Exiv2::ExifData exifData;
            Exiv2::IptcData iptcData;
            Exiv2::XmpData xmpData;
            Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
            Exiv2::TiffParser::encode(*memIo, Data, Size, byteOrder, exifData, iptcData, xmpData);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}