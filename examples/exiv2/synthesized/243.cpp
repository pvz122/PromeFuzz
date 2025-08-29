// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
// Exiv2::FileIo::isopen at basicio.cpp:543:14 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::tell at basicio.cpp:496:16 in basicio.hpp
// Exiv2::FileIo::eof at basicio.cpp:588:14 in basicio.hpp
// Exiv2::FileIo::mmap at basicio.cpp:256:15 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_243(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        FILE* dummy_file = fopen("./dummy_file", "wb");
        if (!dummy_file) return 0;
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);

        Exiv2::FileIo fileIo("./dummy_file");
        if (fileIo.open("r+b") != 0) {
            remove("./dummy_file");
            return 0;
        }

        bool isOpen = fileIo.isopen();
        (void)isOpen;

        size_t ioSize = fileIo.size();
        (void)ioSize;

        size_t tellPos = fileIo.tell();
        (void)tellPos;

        bool eofStatus = fileIo.eof();
        (void)eofStatus;

        Exiv2::byte* mappedData = fileIo.mmap();
        (void)mappedData;

        size_t writeResult = fileIo.write(Data, Size);
        (void)writeResult;

        fileIo.close();
        remove("./dummy_file");

    } catch (...) {
    }

    return 0;
}