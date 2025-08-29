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
#include <cstdlib>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_487(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file for FileIo operations
    std::ofstream dummyFile("./dummy_file", std::ios::binary);
    dummyFile.write(reinterpret_cast<const char*>(Data), Size);
    dummyFile.close();

    try {
        // Test Exiv2::FileIo::tell
        {
            Exiv2::FileIo fileIo("./dummy_file");
            fileIo.open("rb");
            (void)fileIo.tell();
        }

        // Test Exiv2::getULongLong
        {
            Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;
            if (Size >= 8) {
                (void)Exiv2::getULongLong(Data, byteOrder);
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}