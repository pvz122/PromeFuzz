// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
#include <iostream>
#include <vector>
#include <cstdint>
#include <exiv2/exiv2.hpp>

extern "C" int LLVMFuzzerTestOneInput_470(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy vector to use as storage
        std::vector<uint8_t> dummyData(Data, Data + Size);

        // Initialize PtrSliceStorage with proper parameters
        uint8_t* dataPtr = dummyData.data();
        Exiv2::Internal::PtrSliceStorage<uint8_t*> storage(dataPtr, 0, Size);

        // Test unsafeGetIteratorAt
        if (Size > 0) {
            size_t index1 = Data[0] % Size;
            auto it1 = storage.unsafeGetIteratorAt(index1);
        }

        // Test unsafeAt
        if (Size > 0) {
            size_t index2 = Data[Size - 1] % Size;
            const auto& val = storage.unsafeAt(index2);
        }

        // Test begin and end
        auto beginIt = storage.unsafeGetIteratorAt(0);
        auto endIt = storage.unsafeGetIteratorAt(Size);

        // Test at (both const and non-const versions)
        if (Size > 0) {
            size_t index3 = Data[0] % Size;
            try {
                const auto& constVal = storage.unsafeAt(index3);
                auto& nonConstVal = const_cast<uint8_t&>(storage.unsafeAt(index3));
            } catch (...) {
                // Ignore exceptions
            }
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}