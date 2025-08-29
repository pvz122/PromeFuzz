// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::mmap at basicio.cpp:826:14 in basicio.hpp
// Exiv2::MemIo::isopen at basicio.cpp:848:13 in basicio.hpp
// Exiv2::MemIo::putb at basicio.cpp:792:12 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:863:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_339(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    Exiv2::MemIo memIo;

    // Test mmap
    Exiv2::byte* mappedData = memIo.mmap();
    (void)mappedData; // Avoid unused variable warning

    // Test isopen
    bool isOpen = memIo.isopen();
    (void)isOpen; // Avoid unused variable warning

    // Test putb
    memIo.putb(static_cast<Exiv2::byte>(Data[0]));

    // Test write
    if (Size > 1) {
        memIo.write(Data, Size - 1);
    }

    // Test read
    Exiv2::byte* buf = new Exiv2::byte[Size];
    memIo.read(buf, Size);
    delete[] buf;

    // Test close
    memIo.close();

    return 0;
}