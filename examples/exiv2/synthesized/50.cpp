// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifData::end at exif.hpp:439:12 in exif.hpp
// Exiv2::Exifdatum::dataArea at exif.cpp:364:20 in exif.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::DataBuf::write_uint8 at types.cpp:115:22 in types.hpp
// Exiv2::FileIo::open at basicio.cpp:527:13 in basicio.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/exif.hpp>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create ExifData and get end iterator
        Exiv2::ExifData exifData;
        auto it = exifData.end();

        // Create ExifKey and Exifdatum
        Exiv2::ExifKey key(1, "Exif.Image.Make");
        Exiv2::Exifdatum datum(key);

        // Get dataArea from Exifdatum
        Exiv2::DataBuf buf = datum.dataArea();

        // Write uint8 to DataBuf
        if (buf.size() > 0) {
            size_t offset = Data[0] % buf.size();
            buf.write_uint8(offset, Data[0]);
        }

        // Create FileIo and open file
        Exiv2::FileIo fileIo("./dummy_file");
        fileIo.open("rb");

    } catch (...) {
        // Handle all exceptions silently
    }

    return 0;
}