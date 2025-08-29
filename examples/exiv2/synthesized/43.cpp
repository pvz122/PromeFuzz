// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::Jp2Image::writeMetadata at jp2image.cpp:570:16 in jp2image.hpp
// Exiv2::Jp2Image::readMetadata at jp2image.cpp:121:16 in jp2image.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/jp2image.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    static const std::string dummy_file = "./dummy_file.jp2";
    
    // Write input data to dummy file
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Create BasicIo for the dummy file
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        
        // Create Jp2Image instance
        Exiv2::Jp2Image image(std::move(io), false);
        
        if (image.good()) {
            // First write metadata (even though we might not have any)
            image.writeMetadata();
            
            // Then read metadata
            image.readMetadata();
        }
    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    // Clean up
    std::remove(dummy_file.c_str());
    return 0;
}