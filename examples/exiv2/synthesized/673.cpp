// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <exiv2/slice.hpp>

extern "C" int LLVMFuzzerTestOneInput_673(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    const uint8_t* remaining_data = Data + 2 * sizeof(size_t);
    size_t remaining_size = Size - 2 * sizeof(size_t);

    std::vector<uint8_t> vec(remaining_data, remaining_data + remaining_size);

    try {
        // Test with vector as container
        auto slice1 = Exiv2::makeSliceFrom(vec, 0);
        auto subSlice1 = slice1.subSlice(begin, end);

        // Test with raw pointer
        Exiv2::Slice<const uint8_t*> slice2(vec.data(), 0, vec.size());
        auto subSlice2 = slice2.subSlice(begin, end);

        // Test with mutable pointer
        uint8_t* mutable_data = const_cast<uint8_t*>(vec.data());
        Exiv2::Slice<uint8_t*> slice3(mutable_data, 0, vec.size());
        auto subSlice3 = slice3.subSlice(begin, end);

    } catch (const std::out_of_range&) {
        // Handle out_of_range exceptions
    } catch (...) {
        // Handle other exceptions
    }

    return 0;
}