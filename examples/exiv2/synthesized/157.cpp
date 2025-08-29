// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::PreviewManager::getPreviewProperties at preview.cpp:1018:39 in preview.hpp
// Exiv2::PreviewManager::getPreviewImage at preview.cpp:1034:30 in preview.hpp
// Exiv2::PreviewImage::width at preview.cpp:1003:22 in preview.hpp
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
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
#include <exiv2/basicio.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/preview.hpp>
#include <exiv2/types.hpp>
#include <exiv2/asfvideo.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (!outFile) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Test Exiv2::PreviewImage::width
        {
            Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
            if (image.get() != nullptr) {
                image->readMetadata();
                Exiv2::PreviewManager loader(*image);
                Exiv2::PreviewPropertiesList list = loader.getPreviewProperties();
                if (!list.empty()) {
                    Exiv2::PreviewImage preview = loader.getPreviewImage(list[0]);
                    (void)preview.width();
                }
            }
        }

        // Test Exiv2::FileIo::tell
        {
            Exiv2::FileIo fileIo("./dummy_file");
            fileIo.open();
            (void)fileIo.tell();
            fileIo.close();
        }

        // Test Exiv2::getULongLong
        {
            if (Size >= 8) {
                Exiv2::ByteOrder byteOrder = Size % 2 == 0 ? Exiv2::littleEndian : Exiv2::bigEndian;
                (void)Exiv2::getULongLong(Data, byteOrder);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}