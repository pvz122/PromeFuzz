// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::newEpsInstance at epsimage.cpp:1112:18 in epsimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
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
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_498(const uint8_t *Data, size_t Size) {
    try {
        // Create a MemIo instance with the input data
        Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo(Data, Size));

        // Check if the input is an EPS type
        bool isEps = Exiv2::isEpsType(*io, false);
        if (!isEps) {
            return 0;
        }

        // Create an EPS image instance
        bool create = false;
        Exiv2::Image::UniquePtr epsImage = Exiv2::newEpsInstance(std::move(io), create);
        if (!epsImage || !epsImage->good()) {
            return 0;
        }

        // Read metadata
        epsImage->readMetadata();

        // Get MIME type
        std::string mime = epsImage->mimeType();

        // Write metadata (may throw)
        epsImage->writeMetadata();

        // Try to set comment (should throw)
        try {
            epsImage->setComment("test comment");
        } catch (const Exiv2::Error&) {
            // Expected
        }

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    return 0;
}