// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::isRw2Type at rw2image.cpp:203:6 in rw2image.hpp
// Exiv2::isRw2Type at rw2image.cpp:203:6 in rw2image.hpp
// Exiv2::isBmpType at bmpimage.cpp:100:6 in bmpimage.hpp
// Exiv2::isBmpType at bmpimage.cpp:100:6 in bmpimage.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRw2Type at rw2image.cpp:203:6 in rw2image.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRw2Type at rw2image.cpp:203:6 in rw2image.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isBmpType at bmpimage.cpp:100:6 in bmpimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isBmpType at bmpimage.cpp:100:6 in bmpimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
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
#include <exiv2/rw2image.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/epsimage.hpp>
#include <exiv2/bmpimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    if (Size < 24) return 0; // Minimum size for some checks

    // Write data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    if (!outFile) return 0;
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Test with FileIo
        Exiv2::FileIo fileIo("./dummy_file");
        Exiv2::isRafType(fileIo, true);
        Exiv2::isRafType(fileIo, false);
        Exiv2::isRw2Type(fileIo, true);
        Exiv2::isRw2Type(fileIo, false);
        Exiv2::isBmpType(fileIo, true);
        Exiv2::isBmpType(fileIo, false);
        Exiv2::isEpsType(fileIo, true);
        Exiv2::isEpsType(fileIo, false);
        Exiv2::isJpegType(fileIo, true);
        Exiv2::isJpegType(fileIo, false);
        Exiv2::isRiffType(fileIo, true);
        Exiv2::isRiffType(fileIo, false);

        // Test with MemIo
        Exiv2::MemIo memIo;
        memIo.write(Data, Size);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRafType(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRafType(memIo, false);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRw2Type(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRw2Type(memIo, false);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isBmpType(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isBmpType(memIo, false);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isEpsType(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isEpsType(memIo, false);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isJpegType(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isJpegType(memIo, false);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRiffType(memIo, true);
        memIo.seek(0, Exiv2::BasicIo::beg);
        Exiv2::isRiffType(memIo, false);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}