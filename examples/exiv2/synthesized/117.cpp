// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::isCrwType at crwimage.cpp:138:6 in crwimage.hpp
// Exiv2::isPngType at pngimage.cpp:690:6 in pngimage.hpp
// Exiv2::isExvType at jpgimage.cpp:1060:6 in jpgimage.hpp
// Exiv2::isMrwType at mrwimage.cpp:128:6 in mrwimage.hpp
// Exiv2::isCr2Type at cr2image.cpp:137:6 in cr2image.hpp
// Exiv2::isWebPType at webpimage.cpp:687:6 in webpimage.hpp
// Exiv2::isCrwType at crwimage.cpp:138:6 in crwimage.hpp
// Exiv2::isPngType at pngimage.cpp:690:6 in pngimage.hpp
// Exiv2::isExvType at jpgimage.cpp:1060:6 in jpgimage.hpp
// Exiv2::isMrwType at mrwimage.cpp:128:6 in mrwimage.hpp
// Exiv2::isCr2Type at cr2image.cpp:137:6 in cr2image.hpp
// Exiv2::isWebPType at webpimage.cpp:687:6 in webpimage.hpp
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
#include <exiv2/crwimage.hpp>
#include <exiv2/cr2image.hpp>
#include <exiv2/pngimage.hpp>
#include <exiv2/webpimage.hpp>
#include <exiv2/mrwimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test with FileIo
        Exiv2::FileIo fileIo(dummy_file);
        bool advance = Data[0] % 2;

        Exiv2::isCrwType(fileIo, advance);
        Exiv2::isPngType(fileIo, advance);
        Exiv2::isExvType(fileIo, advance);
        Exiv2::isMrwType(fileIo, advance);
        Exiv2::isCr2Type(fileIo, advance);
        Exiv2::isWebPType(fileIo, advance);

        // Test with MemIo
        Exiv2::MemIo memIo(Data, Size);
        Exiv2::isCrwType(memIo, advance);
        Exiv2::isPngType(memIo, advance);
        Exiv2::isExvType(memIo, advance);
        Exiv2::isMrwType(memIo, advance);
        Exiv2::isCr2Type(memIo, advance);
        Exiv2::isWebPType(memIo, advance);
    } catch (...) {
        // Ignore all exceptions
    }

    // Clean up
    remove(dummy_file.c_str());
    return 0;
}