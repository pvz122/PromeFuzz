// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::error at basicio.cpp:584:13 in basicio.hpp
// Exiv2::FileIo::munmap at basicio.cpp:221:13 in basicio.hpp
// Exiv2::MemIo::error at basicio.cpp:884:12 in basicio.hpp
// Exiv2::MemIo::munmap at basicio.cpp:830:12 in basicio.hpp
// Exiv2::RemoteIo::munmap at basicio.cpp:1337:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_399(const uint8_t *Data, size_t Size) {
    // Test FileIo
    {
        const std::string dummy_file = "./dummy_file";
        std::ofstream out(dummy_file, std::ios::binary);
        if (out.is_open()) {
            out.write(reinterpret_cast<const char*>(Data), Size);
            out.close();
        }

        Exiv2::FileIo fileIo(dummy_file);
        fileIo.open();
        fileIo.error();
        fileIo.munmap();
    }

    // Test MemIo
    {
        std::vector<Exiv2::byte> buffer(Data, Data + Size);
        Exiv2::MemIo memIo(buffer.data(), buffer.size());
        memIo.error();
        memIo.munmap();
    }

    // Test RemoteIo
    {
        Exiv2::RemoteIo remoteIo;
        remoteIo.munmap();
    }

    return 0;
}