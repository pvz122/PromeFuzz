// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::XmpParser::decode at xmp.cpp:666:16 in xmp_exiv2.hpp
// Exiv2::XmpParser::terminate at xmp.cpp:623:17 in xmp_exiv2.hpp
// Exiv2::XmpData::empty at xmp.cpp:464:15 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::key at xmp.cpp:308:23 in xmp_exiv2.hpp
// Exiv2::XmpParser::terminate at xmp.cpp:623:17 in xmp_exiv2.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/xmp_exiv2.hpp>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize XMP toolkit
        Exiv2::XmpParser::initialize();
        std::string xmpPacket(reinterpret_cast<const char*>(Data), Size);

        Exiv2::XmpData xmpData;
        int ret = Exiv2::XmpParser::decode(xmpData, xmpPacket);
        if (ret != 0) {
            Exiv2::XmpParser::terminate();
            return 0;
        }

        bool isEmpty = xmpData.empty();
        auto endIter = xmpData.end();

        if (!isEmpty) {
            for (auto it = xmpData.begin(); it != endIter; ++it) {
                std::string key = it->key();
            }
        }

        Exiv2::XmpParser::terminate();
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}