// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::CrwParser::decode at crwimage.cpp:102:17 in crwimage.hpp
// Exiv2::toData at value.hpp:1444:15 in value.hpp
// Exiv2::DataBuf::read_uint32 at types.cpp:136:26 in types.hpp
// Exiv2::DataBuf::alloc at types.cpp:96:15 in types.hpp
// Exiv2::BasicIo::readOrThrow at basicio.cpp:55:15 in basicio.hpp
// Exiv2::CrwParser::encode at crwimage.cpp:115:17 in crwimage.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    try {
        // Test Exiv2::CrwParser::decode
        {
            Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
            io->write(data, size);
            Exiv2::CrwImage crwImage(std::move(io), false);
            Exiv2::CrwParser::decode(&crwImage, data, size);
        }

        // Test Exiv2::toData
        {
            Exiv2::byte buf[8];
            double val = 3.14159;
            Exiv2::toData(buf, val, Exiv2::littleEndian);
        }

        // Test Exiv2::DataBuf::read_uint32
        {
            Exiv2::DataBuf buf(data, size);
            if (size >= 4) {
                buf.read_uint32(0, Exiv2::littleEndian);
            }
        }

        // Test Exiv2::DataBuf::alloc
        {
            Exiv2::DataBuf buf;
            buf.alloc(size);
        }

        // Test Exiv2::BasicIo::readOrThrow
        {
            Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
            io->write(data, size);
            Exiv2::byte readBuf[1024];
            io->seek(0, Exiv2::BasicIo::beg);
            io->readOrThrow(readBuf, std::min(size, sizeof(readBuf)));
        }

        // Test Exiv2::CrwParser::encode
        {
            Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
            io->write(data, size);
            Exiv2::CrwImage crwImage(std::move(io), false);
            Exiv2::Blob blob;
            Exiv2::CrwParser::encode(blob, data, size, &crwImage);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}