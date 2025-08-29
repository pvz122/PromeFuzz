// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isMkvType at matroskavideo.cpp:930:6 in matroskavideo.hpp
// Exiv2::isOrfType at orfimage.cpp:147:6 in orfimage.hpp
// Exiv2::isXmpType at xmpsidecar.cpp:156:6 in xmpsidecar.hpp
// Exiv2::Internal::MatroskaTag::isSkipped at matroskavideo.hpp:83:22 in matroskavideo.hpp
// Exiv2::Internal::MatroskaTag::isComposite at matroskavideo.hpp:86:22 in matroskavideo.hpp
// Exiv2::MatroskaVideo::readMetadata at matroskavideo.cpp:614:21 in matroskavideo.hpp
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
#include <exiv2/xmpsidecar.hpp>
#include <exiv2/orfimage.hpp>
#include <exiv2/matroskavideo.hpp>
#include <fstream>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_124(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    // Create a dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    try {
        // Test isMkvType
        {
            Exiv2::FileIo fileIo("./dummy_file");
            bool advance = (Data[0] % 2) == 0;
            Exiv2::isMkvType(fileIo, advance);
        }

        // Test isOrfType
        {
            Exiv2::FileIo fileIo("./dummy_file");
            bool advance = (Data[1] % 2) == 0;
            Exiv2::isOrfType(fileIo, advance);
        }

        // Test isXmpType
        {
            Exiv2::FileIo fileIo("./dummy_file");
            bool advance = (Data[2] % 2) == 0;
            Exiv2::isXmpType(fileIo, advance);
        }

        // Test MatroskaTag functions
        {
            uint64_t id = *reinterpret_cast<const uint64_t*>(Data);
            std::string label(reinterpret_cast<const char*>(Data), std::min(Size, static_cast<size_t>(100)));
            Exiv2::Internal::MatroskaTag tag(id, label);
            tag.isSkipped();
            tag.isComposite();
        }

        // Test MatroskaVideo::readMetadata
        {
            auto memIo = std::make_unique<Exiv2::MemIo>(Data, Size);
            Exiv2::MatroskaVideo matroskaVideo(std::move(memIo));
            try {
                matroskaVideo.readMetadata();
            } catch (...) {
                // Ignore exceptions
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}