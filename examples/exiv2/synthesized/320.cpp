// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::createIo at image.cpp:812:34 in image.hpp
// Exiv2::isPngType at pngimage.cpp:690:6 in pngimage.hpp
// Exiv2::ImageFactory::open at image.cpp:873:32 in image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
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
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_320(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        Exiv2::BasicIo::UniquePtr io = Exiv2::ImageFactory::createIo("./dummy_file");
        if (!io || io->open() != 0) return 0;

        bool isPng = Exiv2::isPngType(*io, false);
        if (!isPng) {
            io->close();
            return 0;
        }

        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(std::move(io));
        if (!image || !image->good()) return 0;

        image->readMetadata();
        image->writeMetadata();

        std::ostringstream oss;
        image->printStructure(oss, Exiv2::kpsBasic, 0);
        std::string mimeType = image->mimeType();

        image->io().close();

    } catch (const Exiv2::Error& e) {
    } catch (...) {
    }

    return 0;
}