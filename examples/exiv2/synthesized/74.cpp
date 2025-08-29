// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
// Exiv2::DataBuf::cbegin at types.hpp:158:32 in types.hpp
// Exiv2::DataBuf::cend at types.hpp:164:32 in types.hpp
// Exiv2::DataBuf::alloc at types.cpp:96:15 in types.hpp
// Exiv2::DataBuf::alloc at types.cpp:96:15 in types.hpp
// Exiv2::DataBuf::end at types.hpp:161:12 in types.hpp
// Exiv2::DataBuf::reset at types.cpp:104:15 in types.hpp
// Exiv2::DataBuf::empty at types.hpp:196:22 in types.hpp
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    try {
        // Create DataBuf with fuzzed data
        Exiv2::DataBuf buf(Data, Size);

        // Test empty()
        bool isEmpty = buf.empty();

        // Test cbegin() and cend()
        auto begin = buf.cbegin();
        auto end = buf.cend();
        if (!isEmpty) {
            // Iterate through the buffer if not empty
            for (auto it = begin; it != end; ++it) {
                volatile auto ch = *it; // Prevent optimization
            }
        }

        // Test alloc()
        buf.alloc(Size / 2);
        buf.alloc(Size * 2);

        // Test end()
        auto nonConstEnd = buf.end();

        // Test reset()
        buf.reset();
        isEmpty = buf.empty();

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}