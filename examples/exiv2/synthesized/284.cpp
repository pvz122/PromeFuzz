// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::read at basicio.cpp:571:16 in basicio.hpp
// Exiv2::FileIo::read at basicio.cpp:559:17 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:355:16 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
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
#include <vector>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_284(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    try {
        // Initialize RemoteIo with valid data
        Exiv2::MemIo memIo(Data, Size);
        Exiv2::FileIo fileIo("./dummy_file");
        
        // Test RemoteIo::size()
        (void)fileIo.size();

        // Test RemoteIo::read() overloads
        {
            // First overload
            std::vector<Exiv2::byte> buf(Size);
            (void)fileIo.read(buf.data(), Size);

            // Second overload
            (void)fileIo.read(Size);
        }

        // Test RemoteIo::write() overloads
        {
            // First overload (non-functional)
            (void)fileIo.write(Data, Size);

            // Second overload
            (void)fileIo.write(memIo);
        }

        // Test RemoteIo::tell()
        (void)fileIo.tell();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}