// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::RafImage::pixelWidth at rafimage.cpp:31:20 in rafimage.hpp
// Exiv2::RafImage::pixelHeight at rafimage.cpp:41:20 in rafimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::CrwImage::pixelWidth at crwimage.cpp:29:20 in crwimage.hpp
// Exiv2::CrwImage::pixelHeight at crwimage.cpp:37:20 in crwimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmffImage::pixelHeight at bmffimage.cpp:157:21 in bmffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Cr2Image::pixelWidth at cr2image.cpp:29:20 in cr2image.hpp
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
#include <exiv2/crwimage.hpp>
#include <exiv2/bmffimage.hpp>
#include <exiv2/cr2image.hpp>
#include <exiv2/rafimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    static const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        auto rafIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        auto crwIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        auto bmffIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        auto cr2Io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));

        Exiv2::RafImage rafImage(std::move(rafIo), false);
        if (rafImage.good()) {
            (void)rafImage.pixelWidth();
            (void)rafImage.pixelHeight();
        }

        Exiv2::CrwImage crwImage(std::move(crwIo), false);
        if (crwImage.good()) {
            (void)crwImage.pixelWidth();
            (void)crwImage.pixelHeight();
        }

        Exiv2::BmffImage bmffImage(std::move(bmffIo), false);
        if (bmffImage.good()) {
            (void)bmffImage.pixelHeight();
        }

        Exiv2::Cr2Image cr2Image(std::move(cr2Io), false);
        if (cr2Image.good()) {
            (void)cr2Image.pixelWidth();
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}