// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmffImage::pixelWidth at bmffimage.cpp:150:21 in bmffimage.hpp
// Exiv2::BmffImage::pixelHeight at bmffimage.cpp:157:21 in bmffimage.hpp
// Exiv2::BmffImage::parseTiff at bmffimage.cpp:628:17 in bmffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Rw2Image::pixelHeight at rw2image.cpp:40:20 in rw2image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Cr2Image::pixelHeight at cr2image.cpp:37:20 in cr2image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TiffImage::pixelHeight at tiffimage.cpp:113:21 in tiffimage.hpp
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
#include <exiv2/bmffimage.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/cr2image.hpp>
#include <exiv2/rw2image.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_201(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test BmffImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::BmffImage bmffImage(std::move(io), false);
            if (bmffImage.good()) {
                (void)bmffImage.pixelWidth();
                (void)bmffImage.pixelHeight();
                if (Size > 8) {
                    uint32_t root_tag = *reinterpret_cast<const uint32_t*>(Data);
                    uint64_t length = *reinterpret_cast<const uint64_t*>(Data + 4);
                    bmffImage.parseTiff(root_tag, length);
                }
            }
        }

        // Test Rw2Image
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::Rw2Image rw2Image(std::move(io));
            if (rw2Image.good()) {
                (void)rw2Image.pixelHeight();
            }
        }

        // Test Cr2Image
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::Cr2Image cr2Image(std::move(io), false);
            if (cr2Image.good()) {
                (void)cr2Image.pixelHeight();
            }
        }

        // Test TiffImage
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::TiffImage tiffImage(std::move(io), false);
            if (tiffImage.good()) {
                (void)tiffImage.pixelHeight();
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}