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

extern "C" int LLVMFuzzerTestOneInput_333(const uint8_t *Data, size_t Size) {
    try {
        // Write fuzzer input to a dummy file
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        // Create BasicIo instance
        Exiv2::BasicIo::UniquePtr io(new Exiv2::FileIo("./dummy_file"));

        // Check if it's a PSD file
        bool isPsd = Exiv2::isPsdType(*io, true);
        if (!isPsd) return 0;

        // Create PsdImage instance
        Exiv2::Image::UniquePtr image = Exiv2::newPsdInstance(std::move(io), false);
        if (!image) return 0;

        // Test readMetadata
        image->readMetadata();

        // Test writeMetadata
        image->writeMetadata();

        // Test mimeType
        std::string mime = image->mimeType();

        // Test setComment (expect exception)
        try {
            image->setComment("fuzz_comment");
        } catch (const Exiv2::Error&) {
            // Expected exception
        }

    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    } catch (...) {
        // Ignore other exceptions
    }

    return 0;
}