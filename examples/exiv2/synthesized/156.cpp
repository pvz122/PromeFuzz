// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::TiffParser::decode at tiffimage.cpp:207:23 in tiffimage.hpp
// Exiv2::OrfParser::decode at orfimage.cpp:113:22 in orfimage.hpp
// Exiv2::moveXmpToExif at convert.cpp:1344:6 in convert.hpp
// Exiv2::syncExifWithXmp at convert.cpp:1350:6 in convert.hpp
// Exiv2::OrfParser::encode at orfimage.cpp:119:24 in orfimage.hpp
// Exiv2::OrfParser::encode at orfimage.cpp:119:24 in orfimage.hpp
// Exiv2::Cr2Parser::encode at cr2image.cpp:106:24 in cr2image.hpp
// Exiv2::Cr2Parser::encode at cr2image.cpp:106:24 in cr2image.hpp
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
#include <exiv2/convert.hpp>
#include <exiv2/tiffimage.hpp>
#include <exiv2/orfimage.hpp>
#include <exiv2/cr2image.hpp>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize metadata containers
        Exiv2::ExifData exifData;
        Exiv2::IptcData iptcData;
        Exiv2::XmpData xmpData;

        // Test TiffParser::decode
        Exiv2::TiffParser::decode(exifData, iptcData, xmpData, Data, Size);

        // Test OrfParser::decode
        Exiv2::OrfParser::decode(exifData, iptcData, xmpData, Data, Size);

        // Test moveXmpToExif
        Exiv2::moveXmpToExif(xmpData, exifData);

        // Test syncExifWithXmp
        Exiv2::syncExifWithXmp(exifData, xmpData);

        // Prepare for encode functions
        Exiv2::MemIo memIo(Data, Size);
        Exiv2::FileIo fileIo("./dummy_file");
        std::ofstream dummyFile("./dummy_file", std::ios::binary);
        dummyFile.write(reinterpret_cast<const char*>(Data), Size);
        dummyFile.close();

        // Test OrfParser::encode
        Exiv2::OrfParser::encode(memIo, Data, Size, Exiv2::littleEndian, exifData, iptcData, xmpData);
        Exiv2::OrfParser::encode(fileIo, Data, Size, Exiv2::bigEndian, exifData, iptcData, xmpData);

        // Test Cr2Parser::encode
        Exiv2::Cr2Parser::encode(memIo, Data, Size, Exiv2::littleEndian, exifData, iptcData, xmpData);
        Exiv2::Cr2Parser::encode(fileIo, Data, Size, Exiv2::bigEndian, exifData, iptcData, xmpData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}