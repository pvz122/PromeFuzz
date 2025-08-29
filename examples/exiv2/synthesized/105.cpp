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

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::ExifThumbC::writeFile
    try {
        Exiv2::ExifData exifData;
        Exiv2::ExifThumbC thumb(exifData);
        std::string path = "./dummy_thumb";
        thumb.writeFile(path);
    } catch (...) {
        // Ignore exceptions
    }

    // Test Exiv2::Internal::PtrSliceStorage functions
    try {
        std::vector<uint8_t> vec(Data, Data + Size);
        Exiv2::Internal::PtrSliceStorage<uint8_t*> storage(vec.data(), 0, Size);

        if (Size > 0) {
            // Test unsafeAt
            const auto& const_ref = storage.unsafeAt(0);
            auto& mut_ref = storage.unsafeAt(0);

            // Test unsafeGetIteratorAt
            auto const_it = storage.unsafeGetIteratorAt(0);
            auto mut_it = storage.unsafeGetIteratorAt(0);
        }
    } catch (...) {
        // Ignore exceptions
    }

    return 0;
}