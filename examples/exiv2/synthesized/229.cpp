// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_229(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy vector to use as storage
        std::vector<Exiv2::byte> vec(Data, Data + Size);
        Exiv2::byte* data = vec.data();
        size_t begin = 0;
        size_t end = Size;
        
        // Create PtrSliceStorage object
        Exiv2::Internal::PtrSliceStorage<Exiv2::byte*> storage(data, begin, end);

        // Test PtrSliceStorage functions
        size_t index = Data[0] % Size;
        (void)storage.unsafeGetIteratorAt(index);
        (void)storage.unsafeAt(index);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}