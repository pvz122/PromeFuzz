// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::tell at basicio.cpp:834:15 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::tell at basicio.cpp:834:15 in basicio.hpp
// Exiv2::MemIo::eof at basicio.cpp:888:13 in basicio.hpp
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::MemIo memIo(Data, Size);

        // First tell
        (void)memIo.tell();

        // Seek with fuzz data
        int64_t offset = static_cast<int64_t>(Data[0]) - 128; // Make offset potentially negative
        Exiv2::BasicIo::Position pos = static_cast<Exiv2::BasicIo::Position>(Data[0] % 3);
        (void)memIo.seek(offset, pos);

        // Second tell
        (void)memIo.tell();

        // Check EOF
        (void)memIo.eof();

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}