// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
// Exiv2::makeSliceFrom at slice.hpp:545:32 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Internal::SliceBase::size at slice.hpp:29:24 in slice.hpp
// Exiv2::Slice::subSlice at slice.hpp:436:40 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_737(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(size_t)) {
        return 0;
    }

    size_t begin = *reinterpret_cast<const size_t*>(Data);
    size_t end = *reinterpret_cast<const size_t*>(Data + sizeof(size_t));

    // Test with std::vector<int>
    std::vector<int> vec(100);
    for (int i = 0; i < 100; ++i) {
        vec[i] = i;
    }

    try {
        auto slice1 = Exiv2::makeSliceFrom(vec, begin % vec.size());
        if (slice1.size() > 0) {
            size_t subBegin = begin % slice1.size();
            size_t subEnd = end % slice1.size();
            if (subBegin < subEnd) {
                auto subSlice1 = slice1.subSlice(subBegin, subEnd);
                auto constSubSlice1 = slice1.subSlice(subBegin, subEnd);
            }
        }
    } catch (...) {}

    // Test with std::vector<int*>
    std::vector<int*> vecPtr(100);
    for (int i = 0; i < 100; ++i) {
        vecPtr[i] = new int(i);
    }

    try {
        auto slice2 = Exiv2::makeSliceFrom(vecPtr, begin % vecPtr.size());
        if (slice2.size() > 0) {
            size_t subBegin = begin % slice2.size();
            size_t subEnd = end % slice2.size();
            if (subBegin < subEnd) {
                auto subSlice2 = slice2.subSlice(subBegin, subEnd);
                auto constSubSlice2 = slice2.subSlice(subBegin, subEnd);
            }
        }
    } catch (...) {}

    // Test with std::vector<const int*>
    std::vector<const int*> vecConstPtr(100);
    for (int i = 0; i < 100; ++i) {
        vecConstPtr[i] = new int(i);
    }

    try {
        auto slice3 = Exiv2::makeSliceFrom(vecConstPtr, begin % vecConstPtr.size());
        if (slice3.size() > 0) {
            size_t subBegin = begin % slice3.size();
            size_t subEnd = end % slice3.size();
            if (subBegin < subEnd) {
                auto subSlice3 = slice3.subSlice(subBegin, subEnd);
            }
        }
    } catch (...) {}

    // Cleanup
    for (auto ptr : vecPtr) {
        delete ptr;
    }
    for (auto ptr : vecConstPtr) {
        delete ptr;
    }

    return 0;
}