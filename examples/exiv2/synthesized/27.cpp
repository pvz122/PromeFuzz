// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::XmpParser::terminate at xmp.cpp:623:17 in xmp_exiv2.hpp
// Exiv2::PreviewManager::getPreviewProperties at preview.cpp:1018:39 in preview.hpp
// Exiv2::PreviewManager::getPreviewImage at preview.cpp:1034:30 in preview.hpp
// Exiv2::PreviewImage::writeFile at preview.cpp:975:22 in preview.hpp
// Exiv2::XmpParser::terminate at xmp.cpp:623:17 in xmp_exiv2.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize XMP parser
    Exiv2::XmpParser::initialize();

    // Write input data to a dummy file
    std::string filename = "./dummy_file";
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Open the image file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(filename);
        if (!image.get()) {
            Exiv2::XmpParser::terminate();
            return 0;
        }
        image->readMetadata();

        // Create PreviewManager
        Exiv2::PreviewManager previewManager(*image);

        // Get preview properties
        Exiv2::PreviewPropertiesList propertiesList = previewManager.getPreviewProperties();
        if (!propertiesList.empty()) {
            // Get first preview image
            Exiv2::PreviewImage preview = previewManager.getPreviewImage(propertiesList[0]);
            
            // Write preview to file
            preview.writeFile("./preview_output");
        }
    } catch (...) {
        // Catch all exceptions silently
    }

    // Cleanup
    Exiv2::XmpParser::terminate();
    return 0;
}