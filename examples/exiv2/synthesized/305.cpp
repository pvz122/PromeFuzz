// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::newBmffInstance at bmffimage.cpp:785:18 in bmffimage.hpp
// Exiv2::newBmffInstance at bmffimage.cpp:785:18 in bmffimage.hpp
// Exiv2::newQTimeInstance at quicktimevideo.cpp:1600:18 in quicktimevideo.hpp
// Exiv2::newQTimeInstance at quicktimevideo.cpp:1600:18 in quicktimevideo.hpp
// Exiv2::newRafInstance at rafimage.cpp:358:18 in rafimage.hpp
// Exiv2::newRafInstance at rafimage.cpp:358:18 in rafimage.hpp
// Exiv2::newMkvInstance at matroskavideo.cpp:922:18 in matroskavideo.hpp
// Exiv2::newMkvInstance at matroskavideo.cpp:922:18 in matroskavideo.hpp
// Exiv2::newExvInstance at jpgimage.cpp:1053:18 in jpgimage.hpp
// Exiv2::newExvInstance at jpgimage.cpp:1053:18 in jpgimage.hpp
// Exiv2::newGifInstance at gifimage.cpp:67:18 in gifimage.hpp
// Exiv2::newGifInstance at gifimage.cpp:67:18 in gifimage.hpp
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
#include <exiv2/bmffimage.hpp>
#include <exiv2/quicktimevideo.hpp>
#include <exiv2/rafimage.hpp>
#include <exiv2/gifimage.hpp>
#include <exiv2/jpgimage.hpp>
#include <exiv2/matroskavideo.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_305(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        std::ofstream outFile("./dummy_file", std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();

        // Test newBmffInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newBmffInstance(std::move(fileIoPtr), create);
            Exiv2::newBmffInstance(std::move(memIoPtr), create);
        }

        // Test newQTimeInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newQTimeInstance(std::move(fileIoPtr), create);
            Exiv2::newQTimeInstance(std::move(memIoPtr), create);
        }

        // Test newRafInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newRafInstance(std::move(fileIoPtr), create);
            Exiv2::newRafInstance(std::move(memIoPtr), create);
        }

        // Test newMkvInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newMkvInstance(std::move(fileIoPtr), create);
            Exiv2::newMkvInstance(std::move(memIoPtr), create);
        }

        // Test newExvInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newExvInstance(std::move(fileIoPtr), create);
            Exiv2::newExvInstance(std::move(memIoPtr), create);
        }

        // Test newGifInstance
        {
            auto fileIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            auto memIoPtr = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(Data, Size));
            bool create = Data[0] % 2;
            Exiv2::newGifInstance(std::move(fileIoPtr), create);
            Exiv2::newGifInstance(std::move(memIoPtr), create);
        }

    } catch (...) {
    }

    return 0;
}