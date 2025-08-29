// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_626(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    const uint8_t* ptr = Data + 2 * sizeof(size_t);
    size_t data_size = Size - 2 * sizeof(size_t);

    // Create a vector to hold the data
    std::vector<uint8_t> vec(ptr, ptr + data_size);

    try {
        // Test Exiv2::Slice with raw pointer
        {
            Exiv2::Slice<const uint8_t*> slice1(vec.data(), 0, vec.size());
            auto subSlice1 = slice1.subSlice(begin, end);
        }

        // Test mutable slice
        {
            Exiv2::Slice<uint8_t*> slice2(const_cast<uint8_t*>(vec.data()), 0, vec.size());
            auto constSubSlice2 = slice2.subSlice(begin, end);
            auto mutableSubSlice2 = slice2.subSlice(begin, end);
        }

        // Test Exiv2::Slice with const raw pointer
        {
            Exiv2::Slice<const uint8_t*> slice3(vec.data(), 0, vec.size());
            auto subSlice3 = slice3.subSlice(begin, end);
        }

    } catch (const std::out_of_range&) {
        // Handle out_of_range exceptions
    } catch (...) {
        // Ignore other exceptions
    }

    return 0;
}