// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::readFile at basicio.cpp:1703:9 in basicio.hpp
// Exiv2::DataBuf::reset at types.cpp:104:15 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::writeFile at basicio.cpp:1715:8 in basicio.hpp
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_539(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create dummy file
    const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test Exiv2::readFile
        Exiv2::DataBuf buf1 = Exiv2::readFile(dummy_file);

        // Test Exiv2::DataBuf::reset
        buf1.reset();

        // Test Exiv2::writeFile
        Exiv2::DataBuf writeBuf(Size);
        std::memcpy(writeBuf.data(), Data, Size);
        Exiv2::writeFile(writeBuf, dummy_file);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}