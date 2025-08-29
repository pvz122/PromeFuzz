// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSlice at slice.hpp:520:24 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::makeSlice at slice.hpp:528:25 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:553:32 in slice.hpp
// Exiv2::makeSliceUntil at slice.hpp:561:25 in slice.hpp
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_297(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(size_t)) {
        return 0;
    }

    // Extract indices from input data
    size_t begin1 = *reinterpret_cast<const size_t*>(Data);
    size_t end1 = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    size_t begin2 = *reinterpret_cast<const size_t*>(Data + 2 * sizeof(size_t));

    // Create test data
    std::vector<uint8_t> vec(Data, Data + Size);
    uint8_t* ptr = vec.data();

    try {
        // Test makeSlice with vector
        auto slice1 = Exiv2::makeSlice(vec, begin1, end1);
        // Test subSlice
        if (begin1 < end1 && end1 < vec.size()) {
            auto subSlice = slice1.subSlice(begin1, end1);
        }

        // Test makeSlice with pointer
        auto slice2 = Exiv2::makeSlice(ptr, begin1, end1);

        // Test makeSliceUntil with vector
        auto slice3 = Exiv2::makeSliceUntil(vec, end1);

        // Test makeSliceUntil with pointer
        auto slice4 = Exiv2::makeSliceUntil(ptr, end1);

        // Test makeSliceFrom
        auto slice5 = Exiv2::makeSliceFrom(vec, begin2);
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}