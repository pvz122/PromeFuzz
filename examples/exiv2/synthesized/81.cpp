// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::tell at basicio.cpp:834:15 in basicio.hpp
// Exiv2::MemIo::eof at basicio.cpp:888:13 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:856:16 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:774:15 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::size at basicio.cpp:838:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize MemIo with fuzzer input
    Exiv2::MemIo memIo;
    memIo.write(Data, Size);

    // Test tell()
    (void)memIo.tell();

    // Test eof()
    (void)memIo.eof();

    // Test read()
    size_t readSize = Size > 0 ? Data[0] % Size + 1 : 1;
    Exiv2::DataBuf buf = memIo.read(readSize);

    // Test write() with BasicIo
    Exiv2::MemIo srcIo;
    srcIo.write(Data, Size);
    (void)memIo.write(srcIo);

    // Test write() with raw data
    if (Size > 1) {
        size_t writeSize = Data[1] % Size + 1;
        (void)memIo.write(Data, writeSize);
    }

    // Test size()
    (void)memIo.size();

    return 0;
}