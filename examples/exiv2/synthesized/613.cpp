// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_613(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return 0;

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    
    // Create a dummy container
    std::vector<int> vec(100);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = i;
    }

    // Test Exiv2::Slice<int*>::subSlice
    {
        Exiv2::Slice<int*> slice(vec.data(), 0, vec.size());
        try {
            auto constSubSlice = slice.subSlice(begin, end);
            auto mutableSubSlice = slice.subSlice(begin, end);
        } catch (...) {}
    }

    // Test Exiv2::Slice<const int*>::subSlice
    {
        Exiv2::Slice<const int*> constSlice(vec.data(), 0, vec.size());
        try {
            auto subSlice = constSlice.subSlice(begin, end);
        } catch (...) {}
    }

    return 0;
}