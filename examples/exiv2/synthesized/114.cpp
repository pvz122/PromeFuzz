// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::mmap at basicio.cpp:826:14 in basicio.hpp
// Exiv2::MemIo::putb at basicio.cpp:792:12 in basicio.hpp
// Exiv2::MemIo::munmap at basicio.cpp:830:12 in basicio.hpp
// Exiv2::MemIo::path at basicio.cpp:892:27 in basicio.hpp
// Exiv2::MemIo::error at basicio.cpp:884:12 in basicio.hpp
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create MemIo object with fuzzer input
        Exiv2::MemIo memIo(Data, Size);

        // Test mmap
        bool isWriteable = (Data[0] & 1) ? true : false;
        Exiv2::byte* mappedData = memIo.mmap(isWriteable);
        if (mappedData && Size > 0) {
            // Access some data through mmap pointer
            volatile Exiv2::byte dummy = mappedData[Size % Size];
            (void)dummy;
        }

        // Test putb if we have enough data
        if (Size > 1) {
            Exiv2::byte testByte = Data[1];
            memIo.putb(testByte);
        }

        // Test munmap
        memIo.munmap();

        // Test path
        const std::string& path = memIo.path();
        (void)path;

        // Test error
        int err = memIo.error();
        (void)err;

        // Test close
        int closeResult = memIo.close();
        (void)closeResult;

    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}