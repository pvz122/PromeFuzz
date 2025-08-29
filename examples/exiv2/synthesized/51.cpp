// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::fileExists at futils.cpp:233:6 in futils.hpp
// Exiv2::ExifData::empty at exif.hpp:465:22 in exif.hpp
// Exiv2::isoSpeed at easyaccess.cpp:66:26 in easyaccess.hpp
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <futils.hpp>
#include <exif.hpp>
#include <easyaccess.hpp>
#include <string>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    // Write input data to a dummy file
    const std::string dummy_file = "./dummy_file";
    std::ofstream out(dummy_file, std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    // Check if file exists
    bool exists = Exiv2::fileExists(dummy_file);
    if (!exists) {
        return 0;
    }

    // Create ExifData object
    Exiv2::ExifData exifData;

    // Check if ExifData is empty
    bool isEmpty = exifData.empty();

    // Get ISO speed
    Exiv2::ExifData::const_iterator isoIter = Exiv2::isoSpeed(exifData);

    // Get end iterator
    Exiv2::ExifData::iterator endIter = exifData.end();

    return 0;
}