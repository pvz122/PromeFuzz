// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::RemoteIo::path at basicio.cpp:1361:30 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_362(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file
    std::ofstream dummy_file("./dummy_file", std::ios::binary);
    dummy_file.write(reinterpret_cast<const char*>(Data), Size);
    dummy_file.close();

    // Test FileIo
    try {
        Exiv2::FileIo fileIo("./dummy_file");
        fileIo.size(); // Test size()
    } catch (...) {}

    // Test RemoteIo - only test path() since other methods require proper initialization
    try {
        Exiv2::RemoteIo remoteIo;
        remoteIo.path();    // Test path()
    } catch (...) {}

    return 0;
}