// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Internal::ConstSliceBase::subSlice at slice.hpp:133:28 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_319(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return 0;

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));

    // Use std::vector as container type
    std::vector<int> vec(100);
    for (int i = 0; i < 100; ++i) {
        vec[i] = i;
    }

    try {
        // Test Exiv2::Slice<std::vector<int>>::subSlice
        Exiv2::Slice<std::vector<int>> slice1(vec, 0, vec.size());
        auto subSlice1 = slice1.subSlice(begin, end);

        // Test Exiv2::Internal::ConstSliceBase::subSlice
        Exiv2::Internal::ConstSliceBase<Exiv2::Internal::ContainerStorage, std::vector<int>> sliceBase(vec, 0, vec.size());
        auto subSlice2 = sliceBase.subSlice<Exiv2::Slice<std::vector<int>>>(begin, end);

        // Test Exiv2::Slice<const std::vector<int>>::subSlice
        Exiv2::Slice<const std::vector<int>> slice3(vec, 0, vec.size());
        auto subSlice3 = slice3.subSlice(begin, end);

        // Test Exiv2::Slice<int*>::subSlice
        Exiv2::Slice<int*> slice4(vec.data(), 0, vec.size());
        auto subSlice4_const = slice4.subSlice(begin, end); // const overload
        auto subSlice4 = slice4.subSlice(begin, end); // non-const overload

        // Test Exiv2::Slice<const int*>::subSlice
        Exiv2::Slice<const int*> slice5(vec.data(), 0, vec.size());
        auto subSlice5 = slice5.subSlice(begin, end);
    } catch (const std::exception&) {
        // Handle exceptions
    }

    return 0;
}