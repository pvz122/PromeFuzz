// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Jp2Image::printStructure at jp2image.cpp:379:16 in jp2image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::WebPImage::printStructure at webpimage.cpp:401:17 in webpimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Rw2Image::printStructure at rw2image.cpp:62:16 in rw2image.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::RafImage::printStructure at rafimage.cpp:66:16 in rafimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::PngImage::printStructure at pngimage.cpp:180:16 in pngimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Cr2Image::printStructure at cr2image.cpp:45:16 in cr2image.hpp
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
#include <exiv2/rafimage.hpp>
#include <exiv2/jp2image.hpp>
#include <exiv2/rw2image.hpp>
#include <exiv2/cr2image.hpp>
#include <exiv2/pngimage.hpp>
#include <exiv2/webpimage.hpp>
#include <fstream>
#include <iostream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write input data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        std::ostringstream oss;

        // Randomly select an image type and print structure
        switch (Data[0] % 6) {
            case 0: {
                Exiv2::Jp2Image image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
            case 1: {
                Exiv2::WebPImage image(std::move(io));
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
            case 2: {
                Exiv2::Rw2Image image(std::move(io));
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
            case 3: {
                Exiv2::RafImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
            case 4: {
                Exiv2::PngImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
            case 5: {
                Exiv2::Cr2Image image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(oss, static_cast<Exiv2::PrintStructureOption>(Data[1] % 6), Data[2] % 10);
                }
                break;
            }
        }
    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}