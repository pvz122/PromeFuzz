// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_476(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a vector to use as data storage
        std::vector<uint8_t> vec(Data, Data + Size);

        // Initialize PtrSliceStorage
        Exiv2::Internal::PtrSliceStorage storage(vec.data(), 0, Size);

        // Test PtrSliceStorage functions
        size_t index = Data[0] % Size;
        (void)storage.unsafeGetIteratorAt(index % Size);
        (void)storage.unsafeAt(index % Size);

    } catch (...) {
        // Catch all exceptions
    }

    return 0;
}