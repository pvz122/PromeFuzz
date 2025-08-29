// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::DataBuf::reset at types.cpp:104:15 in types.hpp
// Exiv2::readFile at basicio.cpp:1703:9 in basicio.hpp
// Exiv2::writeFile at basicio.cpp:1715:8 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_468(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);
        initialized = true;
    }

    // Test Exiv2::DataBuf::reset
    {
        Exiv2::DataBuf buf(10);
        buf.reset();
    }

    // Test Exiv2::readFile and Exiv2::writeFile
    {
        const std::string path = "./dummy_file";
        std::ofstream outFile(path, std::ios::binary);
        if (outFile.is_open()) {
            outFile.write(reinterpret_cast<const char*>(Data), Size);
            outFile.close();

            try {
                Exiv2::DataBuf buf = Exiv2::readFile(path);
                Exiv2::writeFile(buf, path);
            } catch (...) {
                // Ignore exceptions
            }
        }
    }

    return 0;
}