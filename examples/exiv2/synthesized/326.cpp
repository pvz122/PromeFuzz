// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_326(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) return 0;

    // Extract begin and end indices from input data
    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));

    // Create a dummy container
    std::vector<int> container(100);
    for (size_t i = 0; i < container.size(); ++i) {
        container[i] = i;
    }

    // Test Exiv2::Slice::subSlice
    try {
        Exiv2::Slice<const std::vector<int>> slice1(container, 0, container.size());
        auto subSlice1 = slice1.subSlice(begin, end);
    } catch (...) {}

    // Test Exiv2::Internal::ConstSliceBase::subSlice
    try {
        Exiv2::Slice<const std::vector<int>> slice2(container, 0, container.size());
        auto subSlice2 = slice2.subSlice(begin, end);
    } catch (...) {}

    // Test Exiv2::Slice<const T>::subSlice
    try {
        Exiv2::Slice<const std::vector<int>> slice3(container, 0, container.size());
        auto subSlice3 = slice3.subSlice(begin, end);
    } catch (...) {}

    // Test Exiv2::Slice<T*>::subSlice (both overloads)
    try {
        Exiv2::Slice<std::vector<int>> slice4(container, 0, container.size());
        auto subSlice4_const = slice4.subSlice(begin, end);
        auto subSlice4_mutable = slice4.subSlice(begin, end);
    } catch (...) {}

    // Test Exiv2::Slice<const T*>::subSlice
    try {
        Exiv2::Slice<const std::vector<int>> slice5(container, 0, container.size());
        auto subSlice5 = slice5.subSlice(begin, end);
    } catch (...) {}

    return 0;
}