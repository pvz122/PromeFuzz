// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::path at basicio.cpp:592:28 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::error at basicio.cpp:584:13 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_167(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    const std::string dummy_path = "./dummy_file";
    std::ofstream out(dummy_path, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    // Initialize FileIo object
    Exiv2::FileIo fileIo(dummy_path);

    // Test open() overloads
    fileIo.open();
    fileIo.open("rb");

    // Test path()
    const std::string& path = fileIo.path();

    // Test seek() with different positions
    fileIo.seek(0, Exiv2::BasicIo::beg);
    fileIo.seek(Size / 2, Exiv2::BasicIo::cur);
    fileIo.seek(-1, Exiv2::BasicIo::end);

    // Test error()
    fileIo.error();

    // Test close()
    fileIo.close();

    return 0;
}