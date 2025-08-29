// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::Image::setTypeSupported at image.hpp:443:8 in image.hpp
// Exiv2::ImageFactory::checkMode at image.cpp:765:26 in image.hpp
// Exiv2::newXmpInstance at xmpsidecar.cpp:148:18 in xmpsidecar.hpp
// Exiv2::Image::imageType at image.hpp:449:27 in image.hpp
// Exiv2::Image::checkMode at image.cpp:737:19 in image.hpp
// Exiv2::Image::supportsMetadata at image.cpp:733:13 in image.hpp
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
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test Exiv2::Image::setTypeSupported
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get()) {
            Exiv2::ImageType imageType = static_cast<Exiv2::ImageType>(Data[0] % static_cast<int>(Exiv2::ImageType::riff));
            uint16_t supportedMetadata = static_cast<uint16_t>(Data[0] << 8 | Data[1 % Size]);
            image->setTypeSupported(imageType, supportedMetadata);
        }

        // Test Exiv2::ImageFactory::checkMode
        Exiv2::ImageType type = static_cast<Exiv2::ImageType>(Data[0] % static_cast<int>(Exiv2::ImageType::riff));
        Exiv2::MetadataId metadataId = static_cast<Exiv2::MetadataId>(Data[1 % Size] % 32);
        Exiv2::ImageFactory::checkMode(type, metadataId);

        // Test Exiv2::newXmpInstance
        Exiv2::BasicIo::UniquePtr io(new Exiv2::FileIo("./dummy_file"));
        bool create = Data[0] % 2;
        Exiv2::Image::UniquePtr xmp = Exiv2::newXmpInstance(std::move(io), create);

        // Test Exiv2::Image::imageType
        if (image.get()) {
            Exiv2::ImageType imgType = image->imageType();
            (void)imgType;
        }

        // Test Exiv2::Image::checkMode
        if (image.get()) {
            Exiv2::MetadataId mdId = static_cast<Exiv2::MetadataId>(Data[0] % 32);
            Exiv2::AccessMode mode = image->checkMode(mdId);
            (void)mode;
        }

        // Test Exiv2::Image::supportsMetadata
        if (image.get()) {
            Exiv2::MetadataId mdId = static_cast<Exiv2::MetadataId>(Data[0] % 32);
            bool supported = image->supportsMetadata(mdId);
            (void)supported;
        }

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}