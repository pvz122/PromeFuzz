// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_705(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    const uint8_t* remaining_data = Data + 2 * sizeof(size_t);
    size_t remaining_size = Size - 2 * sizeof(size_t);

    // Create a vector to use as container
    std::vector<uint8_t> vec(remaining_data, remaining_data + remaining_size);

    // Test Exiv2::makeSliceFrom
    try {
        auto slice1 = Exiv2::makeSliceFrom(vec, begin);
        (void)slice1;
    } catch (...) {}

    // Test Exiv2::Slice::subSlice (const container version)
    try {
        auto slice2 = Exiv2::makeSliceFrom(vec, 0);
        auto subSlice2 = slice2.subSlice(begin, end);
        (void)subSlice2;
    } catch (...) {}

    // Test Exiv2::Slice<const T*>::subSlice
    try {
        const uint8_t* ptr = vec.data();
        Exiv2::Slice<const uint8_t*> slice3(ptr, 0, vec.size());
        auto subSlice3 = slice3.subSlice(begin, end);
        (void)subSlice3;
    } catch (...) {}

    // Test Exiv2::Slice<T*>::subSlice (both overloads)
    try {
        uint8_t* ptr = vec.data();
        Exiv2::Slice<uint8_t*> slice4(ptr, 0, vec.size());
        auto subSlice4_const = slice4.subSlice(begin, end);
        auto subSlice4_mutable = slice4.subSlice(begin, end);
        (void)subSlice4_const;
        (void)subSlice4_mutable;
    } catch (...) {}

    // Test Exiv2::Slice<const T*>::subSlice
    try {
        const uint8_t* ptr = vec.data();
        Exiv2::Slice<const uint8_t*> slice5(ptr, 0, vec.size());
        auto subSlice5 = slice5.subSlice(begin, end);
        (void)subSlice5;
    } catch (...) {}

    return 0;
}