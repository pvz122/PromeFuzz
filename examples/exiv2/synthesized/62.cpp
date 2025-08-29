// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
// Exiv2::MemIo::open at basicio.cpp:842:12 in basicio.hpp
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    // Test FileIo functions
    {
        // Write data to dummy file
        std::ofstream outfile("./dummy_file", std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(Data), Size);
        outfile.close();

        Exiv2::FileIo fileIo("./dummy_file");
        
        // Test open() overloads
        fileIo.open();
        fileIo.open("rb");
        fileIo.open("wb");
        
        // Test close()
        fileIo.close();
    }

    // Test MemIo functions
    if (Size > 0) {
        Exiv2::MemIo memIo(Data, Size);
        
        // Test open()
        memIo.open();
        
        // Test putb() with first byte of input
        memIo.putb(Data[0]);
        
        // Test close()
        memIo.close();
    }

    return 0;
}