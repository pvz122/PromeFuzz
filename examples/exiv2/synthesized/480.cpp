// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1082:15 in value.hpp
// Exiv2::readFile at basicio.cpp:1703:9 in basicio.hpp
// Exiv2::writeFile at basicio.cpp:1715:8 in basicio.hpp
// Exiv2::DataBuf::reset at types.cpp:104:15 in types.hpp
// Exiv2::ValueType::dataArea at value.hpp:1679:23 in value.hpp
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_480(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file for readFile/writeFile operations
    const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test Exiv2::readFile
        Exiv2::DataBuf buf1 = Exiv2::readFile(dummy_file);

        // Test Exiv2::writeFile
        Exiv2::writeFile(buf1, dummy_file);

        // Test Exiv2::DataBuf::reset
        buf1.reset();

        // Test Exiv2::ValueType::dataArea with unsigned short
        Exiv2::ValueType<unsigned short> valType(Data, Size, Exiv2::littleEndian);
        Exiv2::DataBuf buf2 = valType.dataArea();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}