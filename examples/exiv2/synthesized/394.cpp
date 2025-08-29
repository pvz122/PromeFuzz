// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::ExifThumbC::writeFile at exif.cpp:379:20 in exif.hpp
// Exiv2::getProcessPath at futils.cpp:355:13 in futils.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "futils.hpp"
#include "types.hpp"
#include "asfvideo.hpp"
#include "exif.hpp"

extern "C" int LLVMFuzzerTestOneInput_394(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Test Exiv2::ExifThumbC::writeFile
    {
        Exiv2::ExifData exifData;
        Exiv2::ExifThumbC thumb(exifData);
        thumb.writeFile("./dummy_file");
    }

    // Test Exiv2::getProcessPath
    {
        std::string path = Exiv2::getProcessPath();
        (void)path;
    }

    // Test Exiv2::DataBuf::size
    {
        Exiv2::DataBuf buf(Size);
        std::memcpy(buf.data(), Data, Size);
        (void)buf.size();
    }

    return 0;
}