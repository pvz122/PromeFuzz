// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::PsdImage::readMetadata at psdimage.cpp:115:16 in psdimage.hpp
// Exiv2::PsdImage::writeMetadata at psdimage.cpp:310:16 in psdimage.hpp
// Exiv2::PsdImage::mimeType at psdimage.cpp:106:23 in psdimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::QuickTimeVideo::readMetadata at quicktimevideo.cpp:555:22 in quicktimevideo.hpp
// Exiv2::QuickTimeVideo::writeMetadata at quicktimevideo.cpp:552:22 in quicktimevideo.hpp
// Exiv2::QuickTimeVideo::mimeType at quicktimevideo.cpp:548:29 in quicktimevideo.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/psdimage.hpp>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/basicio.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_492(const uint8_t *Data, size_t Size) {
    static const std::string dummy_file = "./dummy_file";

    // Write input data to a dummy file
    std::ofstream out(dummy_file, std::ios::binary);
    if (!out) return 0;
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test PsdImage functions
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
            Exiv2::PsdImage psdImage(std::move(io));
            if (psdImage.good()) {
                psdImage.readMetadata();
                psdImage.writeMetadata();
                psdImage.mimeType();
            }
        }

        // Test QuickTimeVideo functions
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
            Exiv2::QuickTimeVideo qtVideo(std::move(io));
            if (qtVideo.good()) {
                qtVideo.readMetadata();
                qtVideo.writeMetadata();
                qtVideo.mimeType();
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}