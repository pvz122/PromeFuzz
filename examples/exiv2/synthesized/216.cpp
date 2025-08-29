// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::FileIo::read at basicio.cpp:559:17 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size) {
    const std::string dummy_file = "./dummy_file";

    // Write data to dummy file
    std::ofstream out(dummy_file, std::ios::binary);
    if (!out.is_open()) {
        return 0;
    }
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    // Initialize FileIo
    Exiv2::FileIo fileIo(dummy_file);

    // Test open()
    if (fileIo.open() != 0) {
        return 0;
    }

    // Test size()
    fileIo.size();

    // Test tell()
    fileIo.tell();

    // Test read()
    if (Size > 0) {
        Exiv2::DataBuf buf = fileIo.read(Size);
    }

    // Test write()
    if (Size > 0) {
        fileIo.write(Data, Size);
    }

    // Test close()
    fileIo.close();

    return 0;
}