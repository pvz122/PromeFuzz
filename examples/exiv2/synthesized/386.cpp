// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_386(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy vector to use as data source
        std::vector<uint8_t> dummyData(Data, Data + Size);

        // Initialize PtrSliceStorage
        Exiv2::Internal::PtrSliceStorage storage(dummyData.data(), 0, Size);

        // Test begin() and end()
        auto begin = storage.unsafeGetIteratorAt(0);
        auto end = storage.unsafeGetIteratorAt(Size > 0 ? Size - 1 : 0);

        // Test at() - const version
        if (Size > 0) {
            try {
                const auto& const_ref = storage.unsafeAt(0);
                (void)const_ref;
            } catch (...) {
                // Catch any exceptions
            }
        }

        // Test unsafeAt() and unsafeGetIteratorAt()
        if (Size > 0) {
            const auto& unsafe_ref = storage.unsafeAt(0);
            auto unsafe_iter = storage.unsafeGetIteratorAt(0);
            (void)unsafe_ref;
            (void)unsafe_iter;
        }

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}