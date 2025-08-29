// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::ExifData::begin at exif.hpp:435:12 in exif.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::Exifdatum::key at exif.cpp:272:24 in exif.hpp
// Exiv2::ExifKey::tag at tags.cpp:313:19 in tags.hpp
// Exiv2::ExifKey::key at tags.cpp:279:22 in tags.hpp
// Exiv2::ExifKey::tagName at tags.cpp:291:22 in tags.hpp
// Exiv2::ExifKey::groupName at tags.cpp:287:22 in tags.hpp
// Exiv2::ExifKey::familyName at tags.cpp:283:22 in tags.hpp
// Exiv2::ExifKey::tagDesc at tags.cpp:301:22 in tags.hpp
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
#include <iostream>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_252(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    try {
        // Create a dummy file with the fuzzer input
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Read the dummy file
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == nullptr) {
            return 0;
        }
        image->readMetadata();

        // Get Exif data
        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) {
            return 0;
        }

        // Iterate through Exif keys and call target functions
        for (Exiv2::ExifData::iterator it = exifData.begin(); it != exifData.end(); ++it) {
            Exiv2::ExifKey key(it->key());

            // Call target functions
            (void)key.tag();
            (void)key.key();
            (void)key.tagName();
            (void)key.groupName();
            (void)key.familyName();
            (void)key.tagDesc();
        }

    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    } catch (...) {
        // Ignore other exceptions
    }

    return 0;
}