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
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <iostream>

extern "C" int LLVMFuzzerTestOneInput_380(const uint8_t *Data, size_t Size) {
    try {
        // Write the input data to a temporary file
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        // Create a BasicIo instance for the file
        Exiv2::BasicIo::UniquePtr io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));

        // Check if the file is a PSD
        bool isPsd = Exiv2::isPsdType(*io, true);
        if (!isPsd) {
            return 0;
        }

        // Create a new PsdImage instance
        Exiv2::Image::UniquePtr image = Exiv2::newPsdInstance(std::move(io), false);
        if (!image.get()) {
            return 0;
        }

        // Read metadata
        image->readMetadata();

        // Write metadata (try to modify and write back)
        image->writeMetadata();

        // Try to set comment (should throw)
        try {
            image->setComment("fuzz_comment");
        } catch (const Exiv2::Error&) {
            // Expected to fail
        }

        // Get MIME type
        std::string mime = image->mimeType();

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    } catch (...) {
        // Ignore any other exceptions
    }

    return 0;
}