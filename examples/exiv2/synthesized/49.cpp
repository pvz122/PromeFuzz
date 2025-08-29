// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::readFile at basicio.cpp:1703:9 in basicio.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
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
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        initialized = true;
    }

    const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    if (!out) {
        return 0;
    }
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        Exiv2::DataBuf buf = Exiv2::readFile(dummy_file);
        if (buf.size() > 0) {
            buf.c_str(0);
            if (buf.size() > 1) {
                buf.c_str(buf.size() - 1);
            }
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}