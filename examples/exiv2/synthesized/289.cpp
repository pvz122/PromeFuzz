// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::size at basicio.cpp:838:15 in basicio.hpp
// Exiv2::MemIo::tell at basicio.cpp:834:15 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:863:15 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:856:16 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
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
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_289(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create and initialize a MemIo object with dummy data
        Exiv2::MemIo memIo;
        memIo.write(Data, Size);

        // Test size() on MemIo
        memIo.size();

        // Test tell() on MemIo
        memIo.tell();

        // Test read() variants on MemIo
        Exiv2::byte buf[1024];
        memIo.read(buf, sizeof(buf));
        Exiv2::DataBuf dbuf = memIo.read(Size);

        // Create a FileIo object for additional testing
        Exiv2::FileIo fileIo("./dummy_file");
        fileIo.write(Data, Size);
        fileIo.size();
        fileIo.tell();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}