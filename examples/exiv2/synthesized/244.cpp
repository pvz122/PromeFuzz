// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::fileProtocol at futils.cpp:210:10 in futils.hpp
// Exiv2::urlencode at futils.cpp:96:13 in futils.hpp
// Exiv2::convertStringCharset at convert.cpp:1388:6 in convert.hpp
// Exiv2::urldecode at futils.cpp:114:6 in futils.hpp
// Exiv2::Uri::Parse at futils.cpp:278:10 in futils.hpp
// Exiv2::fileExists at futils.cpp:233:6 in futils.hpp
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
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_244(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test fileProtocol
    Exiv2::Protocol protocol = Exiv2::fileProtocol(input);

    // Test urlencode
    std::string encoded = Exiv2::urlencode(input);

    // Test convertStringCharset
    std::string str = input;
    bool converted = Exiv2::convertStringCharset(str, "UTF-8", "UCS-2LE");

    // Test urldecode
    std::string urlEncoded = encoded;
    Exiv2::urldecode(urlEncoded);

    // Test Uri::Parse
    Exiv2::Uri uri = Exiv2::Uri::Parse(input);

    // Test fileExists
    bool exists = Exiv2::fileExists(input);

    return 0;
}