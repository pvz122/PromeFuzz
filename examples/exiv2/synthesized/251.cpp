// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:349:29 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeAt at slice.hpp:353:35 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:363:26 in slice.hpp
// Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt at slice.hpp:367:32 in slice.hpp
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

extern "C" int LLVMFuzzerTestOneInput_251(const uint8_t *Data, size_t Size) {
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
            storage.unsafeAt(0);
            const auto& constStorage = storage;
            constStorage.unsafeAt(0);
        }
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::Internal::PtrSliceStorage::unsafeGetIteratorAt
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::PtrSliceStorage<unsigned char*> storage(vec.data(), 0, Size);
        if (Size > 0) {
            storage.unsafeGetIteratorAt(0);
            const auto& constStorage = storage;
            constStorage.unsafeGetIteratorAt(0);
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}