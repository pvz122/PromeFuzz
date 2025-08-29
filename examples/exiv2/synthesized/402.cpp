// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice<const type-parameter-0-0 *>::subSlice at slice.hpp:489:33 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
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
#include <stdexcept>

extern "C" int LLVMFuzzerTestOneInput_402(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    const uint8_t* remaining_data = Data + 2 * sizeof(size_t);
    size_t remaining_size = Size - 2 * sizeof(size_t);

    // Create a vector to use as container
    std::vector<uint8_t> vec(remaining_data, remaining_data + remaining_size);

    try {
        // Test Exiv2::makeSliceFrom
        auto slice1 = Exiv2::makeSliceFrom(vec, begin % (vec.size() + 1));

        // Test Exiv2::Slice::subSlice
        auto subSlice1 = slice1.subSlice(begin % (slice1.size() + 1), end % (slice1.size() + 1));

        // Test Exiv2::Slice<const type-parameter-0-0>::subSlice
        const uint8_t* ptr = vec.data();
        Exiv2::Slice<const uint8_t*> slice2(ptr, 0, vec.size());
        auto subSlice3 = slice2.subSlice(begin % (slice2.size() + 1), end % (slice2.size() + 1));

        // Test Exiv2::Slice<type-parameter-0-0 *>::subSlice
        uint8_t* mutable_ptr = const_cast<uint8_t*>(ptr);
        Exiv2::Slice<uint8_t*> slice3(mutable_ptr, 0, vec.size());
        auto subSlice4 = slice3.subSlice(begin % (slice3.size() + 1), end % (slice3.size() + 1));

        // Test Exiv2::Slice<const type-parameter-0-0 *>::subSlice
        Exiv2::Slice<const uint8_t*> slice4(ptr, 0, vec.size());
        auto subSlice5 = slice4.subSlice(begin % (slice4.size() + 1), end % (slice4.size() + 1));

    } catch (const std::out_of_range&) {
        // Expected exception for out of range accesses
    } catch (...) {
        // Ignore other exceptions
    }

    return 0;
}