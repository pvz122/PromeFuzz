// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSlice at slice.hpp:536:32 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:553:32 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:561:25 in slice.hpp
// Exiv2::makeSlice at slice.hpp:520:24 in slice.hpp
// Exiv2::makeSlice at slice.hpp:536:32 in slice.hpp
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/slice.hpp>
#include <vector>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a vector from input data
    std::vector<uint8_t> vec(Data, Data + Size);

    try {
        // Test Exiv2::Slice<const uint8_t>::subSlice
        if (Size >= 4) {
            size_t begin = Data[0] % (Size / 2);
            size_t end = begin + (Data[1] % (Size - begin));
            auto slice = Exiv2::makeSlice(vec);
            auto subSlice = slice.subSlice(begin, end);
        }

        // Test Exiv2::makeSliceUntil with vector
        if (Size >= 2) {
            size_t end = Data[0] % Size;
            auto sliceUntilVec = Exiv2::makeSliceUntil(vec, end);
        }

        // Test Exiv2::makeSliceUntil with pointer
        if (Size >= 2) {
            size_t end = Data[0] % Size;
            auto sliceUntilPtr = Exiv2::makeSliceUntil(vec.data(), end);
        }

        // Test Exiv2::makeSlice with begin/end
        if (Size >= 4) {
            size_t begin = Data[0] % (Size / 2);
            size_t end = begin + (Data[1] % (Size - begin));
            auto sliceRange = Exiv2::makeSlice(vec, begin, end);
        }

        // Test Exiv2::makeSlice without bounds
        auto sliceFull = Exiv2::makeSlice(vec);

        // Test Exiv2::makeSliceFrom
        if (Size >= 2) {
            size_t begin = Data[0] % Size;
            auto sliceFrom = Exiv2::makeSliceFrom(vec, begin);
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}