// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isExvType at jpgimage.cpp:1060:6 in jpgimage.hpp
// Exiv2::isAsfType at asfvideo.cpp:487:6 in asfvideo.hpp
// Exiv2::isMrwType at mrwimage.cpp:128:6 in mrwimage.hpp
// Exiv2::isXmpType at xmpsidecar.cpp:156:6 in xmpsidecar.hpp
// Exiv2::isPsdType at psdimage.cpp:684:6 in psdimage.hpp
// Exiv2::isPngType at pngimage.cpp:690:6 in pngimage.hpp
// Exiv2::isExvType at jpgimage.cpp:1060:6 in jpgimage.hpp
// Exiv2::isAsfType at asfvideo.cpp:487:6 in asfvideo.hpp
// Exiv2::isMrwType at mrwimage.cpp:128:6 in mrwimage.hpp
// Exiv2::isXmpType at xmpsidecar.cpp:156:6 in xmpsidecar.hpp
// Exiv2::isPsdType at psdimage.cpp:684:6 in psdimage.hpp
// Exiv2::isPngType at pngimage.cpp:690:6 in pngimage.hpp
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
#include <exiv2/pngimage.hpp>
#include <exiv2/mrwimage.hpp>
#include <exiv2/psdimage.hpp>
#include <exiv2/asfvideo.hpp>
#include <exiv2/jpgimage.hpp>

extern "C" int LLVMFuzzerTestOneInput_134(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create MemIo from fuzzer input
        Exiv2::MemIo memIo(Data, Size);

        // Randomly choose advance parameter
        bool advance = Data[0] % 2;

        // Test all type checking functions
        Exiv2::isExvType(memIo, advance);
        Exiv2::isAsfType(memIo, advance);
        Exiv2::isMrwType(memIo, advance);
        Exiv2::isXmpType(memIo, advance);
        Exiv2::isPsdType(memIo, advance);
        Exiv2::isPngType(memIo, advance);

        // Also test with FileIo using dummy file
        const std::string dummyFile = "./dummy_file";
        FILE* f = fopen(dummyFile.c_str(), "wb");
        if (f) {
            fwrite(Data, 1, Size, f);
            fclose(f);

            Exiv2::FileIo fileIo(dummyFile);
            Exiv2::isExvType(fileIo, advance);
            Exiv2::isAsfType(fileIo, advance);
            Exiv2::isMrwType(fileIo, advance);
            Exiv2::isXmpType(fileIo, advance);
            Exiv2::isPsdType(fileIo, advance);
            Exiv2::isPngType(fileIo, advance);

            remove(dummyFile.c_str());
        }
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}