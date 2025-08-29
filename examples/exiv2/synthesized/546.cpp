// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_546(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write data to a dummy file
    std::ofstream file("./dummy_file", std::ios::binary);
    file.write(reinterpret_cast<const char*>(Data), Size);
    file.close();

    try {
        // Test Exiv2::FileIo::tell
        {
            Exiv2::FileIo fileIo("./dummy_file");
            if (fileIo.open("rb") == 0) {
                (void)fileIo.tell();
                fileIo.close();
            }
        }

        // Test Exiv2::getULongLong
        {
            if (Size >= 8) {
                Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
                (void)Exiv2::getULongLong(Data, byteOrder);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}