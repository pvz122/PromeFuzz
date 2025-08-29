// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSlice at slice.hpp:536:32 in slice.hpp
// Exiv2::makeSlice at slice.hpp:520:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:553:32 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:561:25 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a vector from input data
    std::vector<uint8_t> vec(Data, Data + Size);

    try {
        // Test Exiv2::makeSlice (whole container)
        auto slice1 = Exiv2::makeSlice(vec);

        // Test Exiv2::makeSlice (with bounds)
        size_t begin = Data[0] % (Size / 2 + 1);
        size_t end = (Data[1] % (Size - begin)) + begin + 1;
        if (begin < end && end <= Size) {
            auto slice2 = Exiv2::makeSlice(vec, begin, end);

            // Test Exiv2::Slice::subSlice
            size_t sub_begin = Data[0] % (slice2.size() / 2 + 1);
            size_t sub_end = (Data[1] % (slice2.size() - sub_begin)) + sub_begin + 1;
            if (sub_begin < sub_end && sub_end <= slice2.size()) {
                auto sub_slice = slice2.subSlice(sub_begin, sub_end);
            }
        }

        // Test Exiv2::makeSliceFrom
        size_t slice_from_begin = Data[0] % (Size + 1);
        if (slice_from_begin <= Size) {
            auto slice3 = Exiv2::makeSliceFrom(vec, slice_from_begin);
        }

        // Test Exiv2::makeSliceUntil (container version)
        size_t slice_until_end = Data[1] % (Size + 1);
        if (slice_until_end <= Size) {
            auto slice4 = Exiv2::makeSliceUntil(vec, slice_until_end);
        }

        // Test Exiv2::makeSliceUntil (pointer version)
        if (Size > 0) {
            auto slice5 = Exiv2::makeSliceUntil(Data, Size);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}