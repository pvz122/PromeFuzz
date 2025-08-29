// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::WebPImage::printStructure at webpimage.cpp:401:17 in webpimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::RafImage::printStructure at rafimage.cpp:66:16 in rafimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::OrfImage::printStructure at orfimage.cpp:54:16 in orfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::JpegBase::printStructure at jpgimage.cpp:334:16 in jpgimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::TiffImage::printStructure at tiffimage.cpp:262:17 in tiffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmffImage::printStructure at bmffimage.cpp:742:17 in bmffimage.hpp
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
#include <exiv2/orfimage.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/webpimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <fstream>
#include <iostream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(Data), Size);
    outfile.close();

    try {
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        if (!io->open()) return 0;

        // Randomly select an image type to test
        int choice = Data[0] % 6;
        std::ostream null_stream(nullptr);
        Exiv2::PrintStructureOption option = static_cast<Exiv2::PrintStructureOption>(Data[1] % 6);
        size_t depth = Data[2] % 10;

        switch (choice) {
            case 0: {
                Exiv2::WebPImage image(std::move(io));
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
            case 1: {
                Exiv2::RafImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
            case 2: {
                Exiv2::OrfImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
            case 3: {
                Exiv2::JpegImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
            case 4: {
                Exiv2::TiffImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
            case 5: {
                Exiv2::BmffImage image(std::move(io), false);
                if (image.good()) {
                    image.printStructure(null_stream, option, depth);
                }
                break;
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}