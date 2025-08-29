// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::FileIo::open at basicio.cpp:522:13 in basicio.hpp
// Exiv2::FileIo::putb at basicio.cpp:467:13 in basicio.hpp
// Exiv2::FileIo::size at basicio.cpp:506:16 in basicio.hpp
// Exiv2::FileIo::seek at basicio.cpp:473:13 in basicio.hpp
// Exiv2::FileIo::read at basicio.cpp:571:16 in basicio.hpp
// Exiv2::FileIo::write at basicio.cpp:349:16 in basicio.hpp
// Exiv2::FileIo::close at basicio.cpp:547:13 in basicio.hpp
// Exiv2::ExifThumb::setJpegThumbnail at exif.cpp:417:17 in exif.hpp
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
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_410(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize dummy file
    const std::string dummy_file = "./dummy_file";
    {
        std::ofstream out(dummy_file, std::ios::binary);
        out.write(reinterpret_cast<const char*>(Data), Size);
    }

    try {
        // Test FileIo functions
        Exiv2::FileIo fileIo(dummy_file);
        fileIo.open();

        // Test putb
        if (Size > 0) {
            fileIo.putb(static_cast<Exiv2::byte>(Data[0]));
        }

        // Test size
        fileIo.size();

        // Test seek
        fileIo.seek(0, Exiv2::BasicIo::beg);

        // Test read
        if (Size > 1) {
            Exiv2::byte buf[1];
            fileIo.read(buf, 1);
        }

        // Test write
        if (Size > 1) {
            fileIo.write(Data + 1, Size - 1);
        }

        fileIo.close();

        // Test ExifThumb::setJpegThumbnail
        Exiv2::ExifData exifData;
        Exiv2::ExifThumb exifThumb(exifData);
        Exiv2::URational xres(72, 1);
        Exiv2::URational yres(72, 1);
        exifThumb.setJpegThumbnail(Data, Size, xres, yres, 2);

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}