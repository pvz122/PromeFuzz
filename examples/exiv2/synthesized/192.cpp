// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_192(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::ExifThumbC::writeFile
    try {
        Exiv2::ExifData exifData;
        Exiv2::ExifThumbC thumb(exifData);
        thumb.writeFile("./dummy_file");
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::Internal::PtrSliceStorage::unsafeAt
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::PtrSliceStorage<unsigned char*> storage(vec.data(), 0, Size);
        if (Size > 0) {
            const auto& constRef = storage.unsafeAt(0);
            auto& mutableRef = storage.unsafeAt(0);
            (void)constRef;
            (void)mutableRef;
        }
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::PtrSliceStorage<unsigned char*> storage(vec.data(), 0, Size);
        if (Size > 0) {
            auto constIt = storage.unsafeGetIteratorAt(0);
            auto mutableIt = storage.unsafeGetIteratorAt(0);
            (void)constIt;
            (void)mutableIt;
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}