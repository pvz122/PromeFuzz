// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::write_uint8 at types.cpp:115:22 in types.hpp
// Exiv2::DataBuf::begin at types.hpp:155:12 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::base64encode at futils.cpp:140:5 in futils.hpp
// Exiv2::DataBuf::c_data at types.cpp:175:29 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::c_str at types.cpp:185:29 in types.hpp
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
#include <exiv2/futils.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Initialize DataBuf with some size
        Exiv2::DataBuf buf(Size);

        // write_uint8
        for (size_t i = 0; i < Size && i < buf.size(); ++i) {
            buf.write_uint8(i, Data[i]);
        }

        // begin
        auto it = buf.begin();

        // base64encode
        size_t resultSize = ((Size + 2) / 3) * 4 + 1;
        char* result = new char[resultSize];
        Exiv2::base64encode(buf.data(), buf.size(), result, resultSize);
        delete[] result;

        // c_data
        const Exiv2::byte* cdata = buf.c_data(0);

        // data
        Exiv2::byte* data = buf.data(0);

        // c_str
        const char* cstr = buf.c_str(0);

    } catch (...) {
        // Handle exceptions
    }

    return 0;
}