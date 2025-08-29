// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::newBmffInstance at bmffimage.cpp:785:18 in bmffimage.hpp
// Exiv2::newPngInstance at pngimage.cpp:682:18 in pngimage.hpp
// Exiv2::newMrwInstance at mrwimage.cpp:120:18 in mrwimage.hpp
// Exiv2::newBmpInstance at bmpimage.cpp:92:18 in bmpimage.hpp
// Exiv2::newJp2Instance at jp2image.cpp:854:18 in jp2image.hpp
// Exiv2::newXmpInstance at xmpsidecar.cpp:148:18 in xmpsidecar.hpp
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
#include <exiv2/bmffimage.hpp>
#include <exiv2/jp2image.hpp>
#include <exiv2/pngimage.hpp>
#include <exiv2/bmpimage.hpp>
#include <exiv2/mrwimage.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write input data to a dummy file
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    try {
        // Create BasicIo instances
        auto fileIo = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
        auto memIo = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));

        // Randomly choose between file and memory IO
        bool useFileIo = Data[0] % 2;
        auto& io = useFileIo ? fileIo : memIo;

        // Randomly choose create flag
        bool create = Data[0] % 2;

        // Call each target function with new BasicIo instances
        Exiv2::newBmffInstance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);
        Exiv2::newPngInstance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);
        Exiv2::newMrwInstance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);
        Exiv2::newBmpInstance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);
        Exiv2::newJp2Instance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);
        Exiv2::newXmpInstance(Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size)), create);

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}