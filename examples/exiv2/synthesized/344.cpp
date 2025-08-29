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
#include <cassert>

extern "C" int LLVMFuzzerTestOneInput_344(const uint8_t *Data, size_t Size) {
    try {
        Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo(Data, Size));
        bool advance = (Size % 2) == 0;
        Exiv2::isEpsType(*io, advance);

        bool create = (Size % 3) == 0;
        auto epsImage = Exiv2::newEpsInstance(std::move(io), create);
        if (epsImage && epsImage->good()) {
            epsImage->readMetadata();
            epsImage->writeMetadata();
            epsImage->mimeType();

            try {
                epsImage->setComment("dummy_comment");
            } catch (const Exiv2::Error&) {
                // Expected exception
            }
        }
    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    }
    return 0;
}