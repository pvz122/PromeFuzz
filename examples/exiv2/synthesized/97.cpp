// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::isQTimeType at quicktimevideo.cpp:1608:6 in quicktimevideo.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
// Exiv2::isBmffType at bmffimage.cpp:793:6 in bmffimage.hpp
// Exiv2::isTgaType at tgaimage.cpp:99:6 in tgaimage.hpp
// Exiv2::isRafType at rafimage.cpp:366:6 in rafimage.hpp
// Exiv2::isQTimeType at quicktimevideo.cpp:1608:6 in quicktimevideo.hpp
// Exiv2::isEpsType at epsimage.cpp:1120:6 in epsimage.hpp
// Exiv2::isRiffType at riffvideo.cpp:763:6 in riffvideo.hpp
// Exiv2::isBmffType at bmffimage.cpp:793:6 in bmffimage.hpp
// Exiv2::isTgaType at tgaimage.cpp:99:6 in tgaimage.hpp
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
#include <exiv2/tgaimage.hpp>
#include <exiv2/bmffimage.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/riffvideo.hpp>
#include <exiv2/epsimage.hpp>

#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file with the fuzzer input
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Test with FileIo
        Exiv2::FileIo fileIo("./dummy_file");
        bool advance = Data[0] % 2;

        Exiv2::isRafType(fileIo, advance);
        Exiv2::isQTimeType(fileIo, advance);
        Exiv2::isEpsType(fileIo, advance);
        Exiv2::isRiffType(fileIo, advance);
        Exiv2::isBmffType(fileIo, advance);
        Exiv2::isTgaType(fileIo, advance);

        // Test with MemIo
        Exiv2::MemIo memIo(Data, Size);
        Exiv2::isRafType(memIo, advance);
        Exiv2::isQTimeType(memIo, advance);
        Exiv2::isEpsType(memIo, advance);
        Exiv2::isRiffType(memIo, advance);
        Exiv2::isBmffType(memIo, advance);
        Exiv2::isTgaType(memIo, advance);

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}