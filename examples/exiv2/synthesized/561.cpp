// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::getULongLong at types.cpp:257:10 in types.hpp
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
#include <cstdint>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_561(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    // Write data to a dummy file
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    // Test Exiv2::FileIo::tell
    try {
        Exiv2::FileIo fileIo("./dummy_file");
        fileIo.open("rb");
        (void)fileIo.tell();
    } catch (...) {}

    // Test Exiv2::getULongLong
    try {
        Exiv2::ByteOrder order = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
        (void)Exiv2::getULongLong(Data, order);
    } catch (...) {}

    return 0;
}