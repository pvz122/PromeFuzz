// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0>::subSlice at slice.hpp:456:23 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));

    // Create a dummy container
    std::vector<int> container(100);
    for (size_t i = 0; i < container.size(); ++i) {
        container[i] = i;
    }

    // Test Exiv2::Slice::subSlice
    {
        Exiv2::Slice<const std::vector<int>> slice(container, 0, container.size());
        try {
            auto subSlice = slice.subSlice(begin, end);
            (void)subSlice;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::Slice<const T>::subSlice
    {
        Exiv2::Slice<const std::vector<int>> slice(container, 0, container.size());
        try {
            auto subSlice = slice.subSlice(begin, end);
            (void)subSlice;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::Slice<T*>::subSlice (both overloads)
    {
        std::vector<int> data(100);
        std::vector<int>* ptr = &data;
        Exiv2::Slice<std::vector<int>*> slice(ptr, 0, 1);
        try {
            auto constSubSlice = slice.subSlice(0, 1);
            (void)constSubSlice;
            auto mutableSubSlice = slice.subSlice(0, 1);
            (void)mutableSubSlice;
        } catch (...) {
            // Ignore exceptions
        }
    }

    // Test Exiv2::Slice<const T*>::subSlice
    {
        const std::vector<int> data(100);
        const std::vector<int>* ptr = &data;
        Exiv2::Slice<const std::vector<int>*> slice(ptr, 0, 1);
        try {
            auto subSlice = slice.subSlice(0, 1);
            (void)subSlice;
        } catch (...) {
            // Ignore exceptions
        }
    }

    return 0;
}