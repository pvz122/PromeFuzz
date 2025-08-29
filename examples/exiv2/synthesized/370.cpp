// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::ExvImage::mimeType at jpgimage.cpp:1032:23 in jpgimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::WebPImage::mimeType at webpimage.cpp:76:24 in webpimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Jp2Image::mimeType at jp2image.cpp:111:23 in jp2image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::EpsImage::mimeType at epsimage.cpp:1060:23 in epsimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TgaImage::mimeType at tgaimage.cpp:20:23 in tgaimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::PngImage::mimeType at pngimage.cpp:70:23 in pngimage.hpp
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
#include <exiv2/jp2image.hpp>
#include <exiv2/epsimage.hpp>
#include <exiv2/pngimage.hpp>
#include <exiv2/webpimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_370(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        initialized = true;
    }

    if (Size < 1) return 0;

    // Create a dummy file with the fuzzer input
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        
        // Test ExvImage
        Exiv2::ExvImage exvImage(std::move(io), false);
        if (exvImage.good()) {
            exvImage.mimeType();
        }

        // Test WebPImage
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::WebPImage webpImage(std::move(io));
        if (webpImage.good()) {
            webpImage.mimeType();
        }

        // Test Jp2Image
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::Jp2Image jp2Image(std::move(io), false);
        if (jp2Image.good()) {
            jp2Image.mimeType();
        }

        // Test EpsImage
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::EpsImage epsImage(std::move(io), false);
        if (epsImage.good()) {
            epsImage.mimeType();
        }

        // Test TgaImage
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::TgaImage tgaImage(std::move(io));
        if (tgaImage.good()) {
            tgaImage.mimeType();
        }

        // Test PngImage
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        Exiv2::PngImage pngImage(std::move(io), false);
        if (pngImage.good()) {
            pngImage.mimeType();
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}