// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:866:32 in image.hpp
// Exiv2::PreviewManager::getPreviewProperties at preview.cpp:1018:39 in preview.hpp
// Exiv2::PreviewManager::getPreviewImage at preview.cpp:1034:30 in preview.hpp
// Exiv2::PreviewImage::extension at preview.cpp:999:27 in preview.hpp
// Exiv2::PreviewImage::mimeType at preview.cpp:995:27 in preview.hpp
// Exiv2::PreviewImage::width at preview.cpp:1003:22 in preview.hpp
// Exiv2::PreviewImage::height at preview.cpp:1007:22 in preview.hpp
// Exiv2::PreviewImage::width at preview.cpp:1003:22 in preview.hpp
// Exiv2::PreviewImage::height at preview.cpp:1007:22 in preview.hpp
// Exiv2::PreviewImage::size at preview.cpp:991:24 in preview.hpp
// Exiv2::PreviewImage::writeFile at preview.cpp:975:22 in preview.hpp
#include <iostream>
#include <string>
#include <cstdint>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(Data, Size);
        if (image.get() == 0) return 0;
        image->readMetadata();

        Exiv2::PreviewManager manager(*image);
        Exiv2::PreviewPropertiesList list = manager.getPreviewProperties();
        if (!list.empty()) {
            Exiv2::PreviewImage preview = manager.getPreviewImage(list[0]);

            preview.extension();
            preview.mimeType();
            preview.width();
            preview.height();
            preview.width();
            preview.height();
            preview.size();
            preview.writeFile("./dummy_file");

            std::remove("./dummy_file.jpg");
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}