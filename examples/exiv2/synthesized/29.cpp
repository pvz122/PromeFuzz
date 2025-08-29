// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
// Exiv2::DataBuf::alloc at types.cpp:96:15 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
// Exiv2::DataBuf::begin at types.hpp:155:12 in types.hpp
// Exiv2::DataBuf::end at types.hpp:161:12 in types.hpp
// Exiv2::DataBuf::begin at types.hpp:155:12 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    Exiv2::DataBuf buf;

    // First two empty() calls
    (void)buf.empty();
    (void)buf.empty();

    // alloc() with fuzz data size
    if (Size > 0) {
        buf.alloc(Size);
    }

    // size()
    (void)buf.size();

    // begin() and end()
    if (!buf.empty()) {
        (void)buf.begin();
        (void)buf.end();
    }

    // Final begin() call
    (void)buf.begin();

    return 0;
}