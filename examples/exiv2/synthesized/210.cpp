// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:866:32 in image.hpp
// Exiv2::PreviewManager::getPreviewProperties at preview.cpp:1018:39 in preview.hpp
// Exiv2::PreviewManager::getPreviewImage at preview.cpp:1034:30 in preview.hpp
// Exiv2::PreviewImage::copy at preview.cpp:983:23 in preview.hpp
// Exiv2::PreviewImage::extension at preview.cpp:999:27 in preview.hpp
// Exiv2::PreviewImage::pData at preview.cpp:987:27 in preview.hpp
// Exiv2::PreviewImage::id at preview.cpp:1011:25 in preview.hpp
// Exiv2::PreviewImage::height at preview.cpp:1007:22 in preview.hpp
// Exiv2::PreviewImage::writeFile at preview.cpp:975:22 in preview.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/preview.hpp>
#include <exiv2/image.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    try {
        // Create dummy preview data
        std::vector<Exiv2::byte> previewData(data, data + size);
        Exiv2::DataBuf buf(previewData.data(), previewData.size());

        // Get preview images from a dummy image
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(data, size);
        if (image.get() == nullptr) return 0;
        image->readMetadata();
        Exiv2::PreviewManager loader(*image);
        Exiv2::PreviewPropertiesList list = loader.getPreviewProperties();
        if (list.empty()) return 0;

        // Use first preview image
        Exiv2::PreviewImage preview = loader.getPreviewImage(list[0]);

        // Test all target functions
        Exiv2::DataBuf bufCopy = preview.copy();
        std::string ext = preview.extension();
        const Exiv2::byte* pData = preview.pData();
        Exiv2::PreviewId id = preview.id();
        size_t height = preview.height();
        
        // Test writeFile with a dummy path
        preview.writeFile("./dummy_file");

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}