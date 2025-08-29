// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::EpsImage::setComment at epsimage.cpp:1064:16 in epsimage.hpp
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::GifImage::setComment at gifimage.cpp:32:16 in gifimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::RafImage::setComment at rafimage.cpp:61:16 in rafimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::OrfImage::setComment at orfimage.cpp:49:16 in orfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TiffImage::setComment at tiffimage.cpp:126:17 in tiffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::MrwImage::setComment at mrwimage.cpp:51:16 in mrwimage.hpp
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
#include <exiv2/orfimage.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/gifimage.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/epsimage.hpp>
#include <exiv2/mrwimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        initialized = true;
    }

    std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        if (!io->open()) {
            return 0;
        }

        // Test GifImage::setComment
        {
            Exiv2::GifImage gifImage(std::move(io));
            if (gifImage.good()) {
                gifImage.setComment("fuzz_comment");
            }
        }

        // Reset io
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        io->open();

        // Test RafImage::setComment
        {
            Exiv2::RafImage rafImage(std::move(io), false);
            if (rafImage.good()) {
                rafImage.setComment("fuzz_comment");
            }
        }

        // Reset io
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        io->open();

        // Test OrfImage::setComment
        {
            Exiv2::OrfImage orfImage(std::move(io), false);
            if (orfImage.good()) {
                orfImage.setComment("fuzz_comment");
            }
        }

        // Reset io
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        io->open();

        // Test TiffImage::setComment
        {
            Exiv2::TiffImage tiffImage(std::move(io), false);
            if (tiffImage.good()) {
                tiffImage.setComment("fuzz_comment");
            }
        }

        // Reset io
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        io->open();

        // Test MrwImage::setComment
        {
            Exiv2::MrwImage mrwImage(std::move(io), false);
            if (mrwImage.good()) {
                mrwImage.setComment("fuzz_comment");
            }
        }

        // Reset io
        io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        io->open();

        // Test EpsImage::setComment
        {
            Exiv2::EpsImage epsImage(std::move(io), false);
            if (epsImage.good()) {
                epsImage.setComment("fuzz_comment");
            }
        }

    } catch (const Exiv2::Error&) {
        // Expected exceptions, ignore
    }

    return 0;
}