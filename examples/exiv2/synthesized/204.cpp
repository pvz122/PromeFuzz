// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::meteringMode at easyaccess.cpp:338:26 in easyaccess.hpp
// Exiv2::model at easyaccess.cpp:357:26 in easyaccess.hpp
// Exiv2::maxApertureValue at easyaccess.cpp:422:26 in easyaccess.hpp
// Exiv2::flashEnergy at easyaccess.cpp:491:26 in easyaccess.hpp
// Exiv2::serialNumber at easyaccess.cpp:460:26 in easyaccess.hpp
// Exiv2::exposureMode at easyaccess.cpp:200:26 in easyaccess.hpp
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
#include <exiv2/easyaccess.hpp>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_204(const uint8_t *Data, size_t Size) {
    try {
        // Write input data to a dummy file
        std::ofstream file("./dummy_file", std::ios::binary);
        file.write(reinterpret_cast<const char*>(Data), Size);
        file.close();

        // Open the dummy file with Exiv2
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open("./dummy_file");
        if (image.get() == 0) return 0;
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if (exifData.empty()) return 0;

        // Test all target API functions
        Exiv2::meteringMode(exifData);
        Exiv2::model(exifData);
        Exiv2::maxApertureValue(exifData);
        Exiv2::flashEnergy(exifData);
        Exiv2::serialNumber(exifData);
        Exiv2::exposureMode(exifData);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}