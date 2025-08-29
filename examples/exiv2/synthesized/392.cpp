// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
// Exiv2::Internal::ConstSliceBase::cbegin at slice.hpp:113:32 in slice.hpp
// Exiv2::Internal::ConstSliceBase::cend at slice.hpp:120:32 in slice.hpp
// Exiv2::Slice<type-parameter-0-0 *>::subSlice at slice.hpp:504:27 in slice.hpp
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
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_392(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    // Extract begin and end from input data
    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));
    if (begin > end) {
        std::swap(begin, end);
    }

    // Limit the maximum size to prevent excessive memory allocation
    const size_t max_size = 1024;
    if (end > max_size) {
        end = max_size;
    }
    if (begin > end) {
        begin = end;
    }

    // Create a dummy vector for slice storage
    std::vector<int> dummy_data;
    try {
        dummy_data.resize(end);
        for (size_t i = 0; i < end; ++i) {
            dummy_data[i] = i;
        }

        // Test SliceBase::size()
        Exiv2::Internal::SliceBase slice_base(begin, end);
        size_t slice_size = slice_base.size();

        // Test Slice<T*> functions
        Exiv2::Slice<int*> slice(&dummy_data[0], begin, end);
        
        // Test both overloads of subSlice
        if (slice_size > 2) {
            size_t sub_begin = begin % slice_size;
            size_t sub_end = end % slice_size;
            if (sub_begin > sub_end) {
                std::swap(sub_begin, sub_end);
            }
            auto const_sub_slice = slice.subSlice(sub_begin, sub_end);
            auto mutable_sub_slice = slice.subSlice(sub_begin, sub_end);
        }

        // Test ConstSliceBase functions through Slice
        auto const_slice = slice.subSlice(0, slice_size);
        
        // Test cbegin() and cend()
        auto it_begin = const_slice.cbegin();
        auto it_end = const_slice.cend();

        // Test subSlice with valid range
        if (slice_size > 2) {
            size_t sub_begin = begin % slice_size;
            size_t sub_end = end % slice_size;
            if (sub_begin > sub_end) {
                std::swap(sub_begin, sub_end);
            }
            auto sub_slice = const_slice.subSlice(sub_begin, sub_end);
        }
    } catch (const std::exception&) {
        // Ignore exceptions
    }

    return 0;
}