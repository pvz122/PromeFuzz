// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::newPsdInstance at psdimage.cpp:676:18 in psdimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::newOrfInstance at orfimage.cpp:139:18 in orfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::newWebPInstance at webpimage.cpp:679:18 in webpimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::newPgfInstance at pgfimage.cpp:297:18 in pgfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::newEpsInstance at epsimage.cpp:1112:18 in epsimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::newTiffInstance at tiffimage.cpp:239:18 in tiffimage.hpp
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
#include <exiv2/orfimage.hpp>
#include <exiv2/pgfimage.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/epsimage.hpp>
#include <exiv2/webpimage.hpp>
#include <exiv2/psdimage.hpp>

extern "C" int LLVMFuzzerTestOneInput_118(const uint8_t *Data, size_t Size) {
    try {
        Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo(Data, Size));
        
        // Test newPsdInstance
        auto psdImage = Exiv2::newPsdInstance(std::move(io), false);
        if (psdImage.get() && psdImage->good()) {
            psdImage->readMetadata();
        }
        
        io.reset(new Exiv2::MemIo(Data, Size));
        // Test newOrfInstance
        auto orfImage = Exiv2::newOrfInstance(std::move(io), false);
        if (orfImage.get() && orfImage->good()) {
            orfImage->readMetadata();
        }
        
        io.reset(new Exiv2::MemIo(Data, Size));
        // Test newWebPInstance
        auto webpImage = Exiv2::newWebPInstance(std::move(io), false);
        if (webpImage.get() && webpImage->good()) {
            webpImage->readMetadata();
        }
        
        io.reset(new Exiv2::MemIo(Data, Size));
        // Test newPgfInstance
        auto pgfImage = Exiv2::newPgfInstance(std::move(io), false);
        if (pgfImage.get() && pgfImage->good()) {
            pgfImage->readMetadata();
        }
        
        io.reset(new Exiv2::MemIo(Data, Size));
        // Test newEpsInstance
        auto epsImage = Exiv2::newEpsInstance(std::move(io), false);
        if (epsImage.get() && epsImage->good()) {
            epsImage->readMetadata();
        }
        
        io.reset(new Exiv2::MemIo(Data, Size));
        // Test newTiffInstance
        auto tiffImage = Exiv2::newTiffInstance(std::move(io), false);
        if (tiffImage.get() && tiffImage->good()) {
            tiffImage->readMetadata();
        }
    } catch (...) {
        // Handle all exceptions silently
    }
    
    return 0;
}