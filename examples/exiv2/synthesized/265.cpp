// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::enableBMFF at bmffimage.cpp:74:6 in bmffimage.hpp
// Exiv2::isQTimeType at quicktimevideo.cpp:1608:6 in quicktimevideo.hpp
// Exiv2::isBmffType at bmffimage.cpp:793:6 in bmffimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::QuickTimeVideo::readMetadata at quicktimevideo.cpp:555:22 in quicktimevideo.hpp
// Exiv2::QuickTimeVideo::mimeType at quicktimevideo.cpp:548:29 in quicktimevideo.hpp
// Exiv2::QuickTimeVideo::writeMetadata at quicktimevideo.cpp:552:22 in quicktimevideo.hpp
// Exiv2::isQTimeType at quicktimevideo.cpp:1608:6 in quicktimevideo.hpp
// Exiv2::isBmffType at bmffimage.cpp:793:6 in bmffimage.hpp
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
#include <exiv2/bmffimage.hpp>
#include <exiv2/quicktimevideo.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_265(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        initialized = true;
    }

    // Test enableBMFF
    bool bmffEnabled = Exiv2::enableBMFF(true);
    (void)bmffEnabled;

    // Write input data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (!outFile) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Test isQTimeType and isBmffType with FileIo
        Exiv2::FileIo fileIo("./dummy_file");
        bool isQTime = Exiv2::isQTimeType(fileIo, false);
        bool isBmff = Exiv2::isBmffType(fileIo, false);
        (void)isQTime;
        (void)isBmff;

        // Test QuickTimeVideo functions
        auto memIo = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
        Exiv2::QuickTimeVideo qtVideo(std::move(memIo));
        if (qtVideo.good()) {
            try {
                qtVideo.readMetadata();
                std::string mime = qtVideo.mimeType();
                (void)mime;
                qtVideo.writeMetadata();
            } catch (...) {
                // Ignore exceptions
            }
        }

        // Test with MemIo
        auto memIo2 = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
        isQTime = Exiv2::isQTimeType(*memIo2, true);
        isBmff = Exiv2::isBmffType(*memIo2, true);
        (void)isQTime;
        (void)isBmff;
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}