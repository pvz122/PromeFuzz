// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::error at basicio.cpp:584:13 in basicio.hpp
// Exiv2::FileIo::eof at basicio.cpp:588:14 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    static const std::string dummy_file = "./dummy_file";

    // Write input data to dummy file
    std::ofstream out(dummy_file, std::ios::binary);
    if (!out.is_open()) {
        return 0;
    }
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    // Initialize FileIo object
    Exiv2::FileIo fileIo(dummy_file);

    // Open the file
    if (fileIo.open() != 0) {
        return 0;
    }

    // Perform seek operations
    fileIo.seek(0, Exiv2::BasicIo::beg);
    fileIo.seek(Size / 2, Exiv2::BasicIo::cur);
    fileIo.seek(-1, Exiv2::BasicIo::end);

    // Check error state
    fileIo.error();

    // Check EOF
    fileIo.eof();

    return 0;
}