// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::MemIo::open at basicio.cpp:842:12 in basicio.hpp
// Exiv2::MemIo::getb at basicio.cpp:876:12 in basicio.hpp
// Exiv2::MemIo::putb at basicio.cpp:792:12 in basicio.hpp
// Exiv2::MemIo::read at basicio.cpp:863:15 in basicio.hpp
// Exiv2::MemIo::write at basicio.cpp:738:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize MemIo with fuzzer input
    Exiv2::MemIo io(Data, Size);

    // Test open()
    io.open();

    // Test getb() and putb()
    int byte = io.getb();
    if (byte != EOF) {
        io.putb(static_cast<Exiv2::byte>(byte));
    }

    // Test read() and write()
    const size_t buf_size = 64;
    Exiv2::byte buf[buf_size];
    size_t read_count = io.read(buf, buf_size);
    if (read_count > 0) {
        io.write(buf, read_count);
    }

    // Test close()
    io.close();

    return 0;
}