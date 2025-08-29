// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::ExvImage::mimeType at jpgimage.cpp:1032:23 in jpgimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TiffImage::mimeType at tiffimage.cpp:59:24 in tiffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmpImage::mimeType at bmpimage.cpp:25:23 in bmpimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TgaImage::mimeType at tgaimage.cpp:20:23 in tgaimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::PsdImage::mimeType at psdimage.cpp:106:23 in psdimage.hpp
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
#include <exiv2/tgaimage.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/preview.hpp>
#include <exiv2/bmpimage.hpp>
#include <exiv2/psdimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        initialized = true;
    }

    // Write input data to a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test ExvImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            Exiv2::ExvImage exvImage(std::move(io), false);
            if (exvImage.good()) {
                exvImage.mimeType();
            }
        }

        // Test TiffImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            Exiv2::TiffImage tiffImage(std::move(io), false);
            if (tiffImage.good()) {
                tiffImage.mimeType();
            }
        }

        // Test BmpImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            Exiv2::BmpImage bmpImage(std::move(io));
            if (bmpImage.good()) {
                bmpImage.mimeType();
            }
        }

        // Test TgaImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            Exiv2::TgaImage tgaImage(std::move(io));
            if (tgaImage.good()) {
                tgaImage.mimeType();
            }
        }

        // Test PsdImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            Exiv2::PsdImage psdImage(std::move(io));
            if (psdImage.good()) {
                psdImage.mimeType();
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}