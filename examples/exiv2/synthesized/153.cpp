// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::OrfImage::pixelWidth at orfimage.cpp:33:20 in orfimage.hpp
// Exiv2::OrfImage::pixelHeight at orfimage.cpp:41:20 in orfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::CrwImage::pixelWidth at crwimage.cpp:29:20 in crwimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::MrwImage::pixelWidth at mrwimage.cpp:25:20 in mrwimage.hpp
// Exiv2::MrwImage::pixelHeight at mrwimage.cpp:33:20 in mrwimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::RafImage::pixelHeight at rafimage.cpp:41:20 in rafimage.hpp
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
#include <exiv2/mrwimage.hpp>
#include <exiv2/crwimage.hpp>
#include <exiv2/orfimage.hpp>
#include <exiv2/rafimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_153(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write input data to a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test OrfImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::OrfImage image(std::move(io), false);
            if (image.good()) {
                (void)image.pixelWidth();
                (void)image.pixelHeight();
            }
        }

        // Test CrwImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::CrwImage image(std::move(io), false);
            if (image.good()) {
                (void)image.pixelWidth();
            }
        }

        // Test MrwImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::MrwImage image(std::move(io), false);
            if (image.good()) {
                (void)image.pixelWidth();
                (void)image.pixelHeight();
            }
        }

        // Test RafImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::RafImage image(std::move(io), false);
            if (image.good()) {
                (void)image.pixelHeight();
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}