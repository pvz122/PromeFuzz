// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::putb at basicio.cpp:467:13 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::error at basicio.cpp:584:13 in basicio.hpp
// Exiv2::FileIo::populateFakeData at basicio.cpp:596:14 in basicio.hpp
// Exiv2::FileIo::read at basicio.cpp:571:16 in basicio.hpp
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
#include <exiv2/basicio.hpp>
#include <fstream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const std::string dummy_file = "./dummy_file";
    {
        std::ofstream out(dummy_file, std::ios::binary);
        if (!out) return 0;
        out.write(reinterpret_cast<const char*>(Data), Size);
    }

    Exiv2::FileIo fileIo(dummy_file);
    if (fileIo.open() != 0) return 0;

    // Test putb
    if (Size > 0) {
        fileIo.putb(static_cast<Exiv2::byte>(Data[0]));
    }

    // Test size
    fileIo.size();

    // Test seek
    fileIo.seek(0, Exiv2::BasicIo::beg);
    fileIo.seek(Size / 2, Exiv2::BasicIo::cur);
    fileIo.seek(-1, Exiv2::BasicIo::end);

    // Test error
    fileIo.error();

    // Test populateFakeData
    fileIo.populateFakeData();

    // Test read
    if (Size > 1) {
        Exiv2::byte buf[1];
        fileIo.read(buf, 1);
    }

    fileIo.close();
    return 0;
}