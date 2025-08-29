// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isGifType at gifimage.cpp:75:6 in gifimage.hpp
// Exiv2::isGifType at gifimage.cpp:75:6 in gifimage.hpp
// Exiv2::isOrfType at orfimage.cpp:147:6 in orfimage.hpp
// Exiv2::isOrfType at orfimage.cpp:147:6 in orfimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isJp2Type at jp2image.cpp:862:6 in jp2image.hpp
// Exiv2::isJp2Type at jp2image.cpp:862:6 in jp2image.hpp
// Exiv2::isTiffType at tiffimage.cpp:247:6 in tiffimage.hpp
// Exiv2::isTiffType at tiffimage.cpp:247:6 in tiffimage.hpp
// Exiv2::isPgfType at pgfimage.cpp:305:6 in pgfimage.hpp
// Exiv2::isPgfType at pgfimage.cpp:305:6 in pgfimage.hpp
// Exiv2::isGifType at gifimage.cpp:75:6 in gifimage.hpp
// Exiv2::isGifType at gifimage.cpp:75:6 in gifimage.hpp
// Exiv2::isOrfType at orfimage.cpp:147:6 in orfimage.hpp
// Exiv2::isOrfType at orfimage.cpp:147:6 in orfimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isJpegType at jpgimage.cpp:1013:6 in jpgimage.hpp
// Exiv2::isJp2Type at jp2image.cpp:862:6 in jp2image.hpp
// Exiv2::isJp2Type at jp2image.cpp:862:6 in jp2image.hpp
// Exiv2::isTiffType at tiffimage.cpp:247:6 in tiffimage.hpp
// Exiv2::isTiffType at tiffimage.cpp:247:6 in tiffimage.hpp
// Exiv2::isPgfType at pgfimage.cpp:305:6 in pgfimage.hpp
// Exiv2::isPgfType at pgfimage.cpp:305:6 in pgfimage.hpp
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
#include <exiv2/gifimage.hpp>
#include <exiv2/jp2image.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/jpgimage.hpp>

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    try {
        // Test with MemIo
        Exiv2::MemIo memIo(Data, Size);
        Exiv2::isGifType(memIo, true);
        Exiv2::isGifType(memIo, false);
        Exiv2::isOrfType(memIo, true);
        Exiv2::isOrfType(memIo, false);
        Exiv2::isJpegType(memIo, true);
        Exiv2::isJpegType(memIo, false);
        Exiv2::isJp2Type(memIo, true);
        Exiv2::isJp2Type(memIo, false);
        Exiv2::isTiffType(memIo, true);
        Exiv2::isTiffType(memIo, false);
        Exiv2::isPgfType(memIo, true);
        Exiv2::isPgfType(memIo, false);

        // Test with FileIo
        const std::string dummyFile = "./dummy_file";
        FILE* f = fopen(dummyFile.c_str(), "wb");
        if (!f) return 0;
        fwrite(Data, 1, Size, f);
        fclose(f);

        Exiv2::FileIo fileIo(dummyFile);
        Exiv2::isGifType(fileIo, true);
        Exiv2::isGifType(fileIo, false);
        Exiv2::isOrfType(fileIo, true);
        Exiv2::isOrfType(fileIo, false);
        Exiv2::isJpegType(fileIo, true);
        Exiv2::isJpegType(fileIo, false);
        Exiv2::isJp2Type(fileIo, true);
        Exiv2::isJp2Type(fileIo, false);
        Exiv2::isTiffType(fileIo, true);
        Exiv2::isTiffType(fileIo, false);
        Exiv2::isPgfType(fileIo, true);
        Exiv2::isPgfType(fileIo, false);

        remove(dummyFile.c_str());
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}