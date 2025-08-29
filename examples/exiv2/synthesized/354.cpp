// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::meteringMode at easyaccess.cpp:338:26 in easyaccess.hpp
// Exiv2::sharpness at easyaccess.cpp:306:26 in easyaccess.hpp
// Exiv2::getEnv at futils.cpp:77:13 in futils.hpp
// Exiv2::saturation at easyaccess.cpp:293:26 in easyaccess.hpp
// Exiv2::Cr2Image::pixelWidth at cr2image.cpp:29:20 in cr2image.hpp
// Exiv2::make at easyaccess.cpp:349:26 in easyaccess.hpp
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
#include <exiv2/futils.hpp>
#include <exiv2/cr2image.hpp>
#include <exiv2/easyaccess.hpp>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_354(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file for Cr2Image
    std::ofstream out("./dummy_file", std::ios::binary);
    out.write(reinterpret_cast<const char*>(Data), Size);
    out.close();

    try {
        // Test Exiv2::meteringMode
        {
            Exiv2::ExifData ed;
            Exiv2::meteringMode(ed);
        }

        // Test Exiv2::sharpness
        {
            Exiv2::ExifData ed;
            Exiv2::sharpness(ed);
        }

        // Test Exiv2::getEnv
        {
            int env_var = Data[0] % 10; // Limit to reasonable range
            Exiv2::getEnv(env_var);
        }

        // Test Exiv2::saturation
        {
            Exiv2::ExifData ed;
            Exiv2::saturation(ed);
        }

        // Test Exiv2::Cr2Image::pixelWidth
        {
            auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo("./dummy_file"));
            Exiv2::Cr2Image image(std::move(io), false);
            image.pixelWidth();
        }

        // Test Exiv2::make
        {
            Exiv2::ExifData ed;
            Exiv2::make(ed);
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}