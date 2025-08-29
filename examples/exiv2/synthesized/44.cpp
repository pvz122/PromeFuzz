// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Uri::Parse at futils.cpp:278:10 in futils.hpp
// Exiv2::Uri::Decode at futils.cpp:270:11 in futils.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/futils.hpp>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    try {
        std::string uri_str(reinterpret_cast<const char*>(Data), Size);
        Exiv2::Uri uri = Exiv2::Uri::Parse(uri_str);
        Exiv2::Uri::Decode(uri);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}