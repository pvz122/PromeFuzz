// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::eof at basicio.cpp:888:13 in basicio.hpp
// Exiv2::MemIo::open at basicio.cpp:842:12 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::seek at basicio.cpp:798:12 in basicio.hpp
// Exiv2::MemIo::getb at basicio.cpp:876:12 in basicio.hpp
// Exiv2::MemIo::putb at basicio.cpp:792:12 in basicio.hpp
// Exiv2::RemoteIo::putb at basicio.cpp:1219:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_440(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize MemIo with fuzzer input
    Exiv2::MemIo memIo(Data, Size);

    // Test eof()
    bool isEof = memIo.eof();

    // Test open()
    int openResult = memIo.open();

    // Test seek() with various positions and offsets
    int seekResult1 = memIo.seek(0, Exiv2::BasicIo::beg);
    int seekResult2 = memIo.seek(Size / 2, Exiv2::BasicIo::cur);
    int seekResult3 = memIo.seek(-1 * (Size / 2), Exiv2::BasicIo::cur);
    int seekResult4 = memIo.seek(0, Exiv2::BasicIo::end);

    // Test getb() and putb() in sequence
    memIo.seek(0, Exiv2::BasicIo::beg);
    for (size_t i = 0; i < Size; ++i) {
        int byteRead = memIo.getb();
        if (byteRead != EOF) {
            int byteWritten = memIo.putb(static_cast<Exiv2::byte>(byteRead));
            (void)byteWritten; // Avoid unused variable warning
        }
    }

    // Test RemoteIo's putb (always returns 0)
    Exiv2::RemoteIo remoteIo;
    int remotePutResult = remoteIo.putb(static_cast<Exiv2::byte>(Data[0]));

    return 0;
}