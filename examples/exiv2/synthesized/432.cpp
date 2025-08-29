// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isPsdType at psdimage.cpp:684:6 in psdimage.hpp
// Exiv2::newPsdInstance at psdimage.cpp:676:18 in psdimage.hpp
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
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_432(const uint8_t *Data, size_t Size) {
    try {
        // Write input data to a temporary file
        std::ofstream out("./dummy_file", std::ios::binary);
        if (!out) return 0;
        out.write(reinterpret_cast<const char*>(Data), Size);
        if (!out) return 0;
        out.close();

        // Create BasicIo instance and validate
        Exiv2::BasicIo::UniquePtr io(new Exiv2::FileIo("./dummy_file"));
        if (!io->isopen()) return 0;

        // Check if file is PSD type
        bool isPsd = Exiv2::isPsdType(*io, false);
        if (!isPsd) return 0;

        // Create PsdImage instance
        Exiv2::Image::UniquePtr image = Exiv2::newPsdInstance(std::move(io), false);
        if (!image.get()) return 0;

        // Test readMetadata
        image->readMetadata();

        // Test writeMetadata
        image->writeMetadata();

        // Test mimeType
        std::string mime = image->mimeType();

        // Test setComment (expect exception)
        try {
            image->setComment("test comment");
        } catch (const Exiv2::Error&) {
            // Expected exception
        }

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    return 0;
}