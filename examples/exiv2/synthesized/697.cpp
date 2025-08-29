// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
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
#include <exiv2/basicio.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/preview.hpp>
#include <exiv2/types.hpp>
#include <exiv2/asfvideo.hpp>

extern "C" int LLVMFuzzerTestOneInput_697(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    // Test Exiv2::getULongLong
    try {
        Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
        (void)Exiv2::getULongLong(Data, byteOrder);
    } catch (...) {}

    // Test Exiv2::FileIo::tell
    try {
        Exiv2::FileIo fileIo("./dummy_file");
        fileIo.open("rb");
        (void)fileIo.tell();
        fileIo.close();
    } catch (...) {}

    return 0;
}