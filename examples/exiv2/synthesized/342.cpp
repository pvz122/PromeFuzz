// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::mmap at basicio.cpp:826:14 in basicio.hpp
// Exiv2::MemIo::isopen at basicio.cpp:848:13 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:863:15 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::putb at basicio.cpp:792:12 in basicio.hpp
// Exiv2::MemIo::close at basicio.cpp:852:12 in basicio.hpp
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_342(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize MemIo with fuzzer input
    Exiv2::MemIo memIo(Data, Size);

    // Test mmap
    Exiv2::byte* mappedData = memIo.mmap();
    if (mappedData && Size > 0) {
        // Access some data to ensure it's readable
        volatile Exiv2::byte dummy = mappedData[0];
        (void)dummy;
    }

    // Test isopen
    bool isOpen = memIo.isopen();
    (void)isOpen;

    // Test read
    Exiv2::byte readBuf[1024];
    size_t bytesRead = memIo.read(readBuf, sizeof(readBuf));
    (void)bytesRead;

    // Test write - use a small buffer to avoid excessive memory usage
    Exiv2::byte writeBuf[16];
    if (Size > sizeof(writeBuf)) {
        memcpy(writeBuf, Data, sizeof(writeBuf));
        size_t bytesWritten = memIo.write(writeBuf, sizeof(writeBuf));
        (void)bytesWritten;
    }

    // Test putb - write a single byte
    if (Size > 0) {
        int putResult = memIo.putb(Data[0]);
        (void)putResult;
    }

    // Test close
    int closeResult = memIo.close();
    (void)closeResult;

    return 0;
}