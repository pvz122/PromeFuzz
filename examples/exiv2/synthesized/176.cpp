// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::AsciiValue::clone at value.hpp:437:13 in value.hpp
// Exiv2::AsciiValue::write at value.cpp:258:27 in value.hpp
// Exiv2::OrfParser::decode at orfimage.cpp:113:22 in orfimage.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::OrfImage::printStructure at orfimage.cpp:54:16 in orfimage.hpp
// Exiv2::OrfParser::encode at orfimage.cpp:119:24 in orfimage.hpp
// Exiv2::copyXmpToIptc at convert.cpp:1376:6 in convert.hpp
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
#include <iostream>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_176(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::AsciiValue::clone
    {
        Exiv2::AsciiValue asciiValue;
        auto cloned = asciiValue.clone();
        if (!cloned) return 0;
    }

    // Test Exiv2::AsciiValue::write
    {
        Exiv2::AsciiValue asciiValue;
        std::ostringstream os;
        asciiValue.write(os);
    }

    // Test Exiv2::OrfParser::decode
    {
        try {
            Exiv2::ExifData exifData;
            Exiv2::IptcData iptcData;
            Exiv2::XmpData xmpData;
            Exiv2::OrfParser::decode(exifData, iptcData, xmpData, Data, Size);
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::OrfImage::printStructure
    {
        try {
            std::ofstream dummyFile("./dummy_file", std::ios::binary);
            if (!dummyFile) return 0;
            dummyFile.write(reinterpret_cast<const char*>(Data), Size);
            dummyFile.close();

            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            if (!io->open() == 0) return 0;
            Exiv2::OrfImage image(std::move(io), false);
            if (!image.good()) return 0;
            std::ostringstream os;
            image.printStructure(os, Exiv2::kpsBasic, 0);
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::OrfParser::encode
    {
        try {
            Exiv2::ExifData exifData;
            Exiv2::IptcData iptcData;
            Exiv2::XmpData xmpData;
            std::ofstream dummyFile("./dummy_file", std::ios::binary);
            if (!dummyFile) return 0;
            dummyFile.write(reinterpret_cast<const char*>(Data), Size);
            dummyFile.close();

            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            if (!io->open() == 0) return 0;
            Exiv2::OrfParser::encode(*io, Data, Size, Exiv2::littleEndian, exifData, iptcData, xmpData);
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::copyXmpToIptc
    {
        Exiv2::XmpData xmpData;
        Exiv2::IptcData iptcData;
        Exiv2::copyXmpToIptc(xmpData, iptcData);
    }

    return 0;
}