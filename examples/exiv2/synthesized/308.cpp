// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::createIo at image.cpp:812:34 in image.hpp
// Exiv2::ImageFactory::getType at image.cpp:800:25 in image.hpp
// Exiv2::ImageFactory::checkType at image.cpp:780:20 in image.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ImageFactory::create at image.cpp:902:32 in image.hpp
// Exiv2::ImageFactory::create at image.cpp:886:32 in image.hpp
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

extern "C" int LLVMFuzzerTestOneInput_308(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);
        initialized = true;
    }

    if (Size < 1) {
        return 0;
    }

    try {
        // Write data to a temporary file
        std::string file_path = "./dummy_file";
        std::ofstream out_file(file_path, std::ios::binary);
        out_file.write(reinterpret_cast<const char*>(Data), Size);
        out_file.close();

        // Test createIo
        bool useCurl = (Data[0] & 1) == 0;
        Exiv2::BasicIo::UniquePtr io = Exiv2::ImageFactory::createIo(file_path, useCurl);
        if (!io || !io->isopen()) {
            return 0;
        }

        // Test getType
        Exiv2::ImageType img_type = Exiv2::ImageFactory::getType(*io);
        if (img_type == Exiv2::ImageType::none) {
            return 0;
        }

        // Test checkType - only if io is valid and opened
        bool advance = (Data[0] & 2) == 0;
        if (io->open() == 0) {
            Exiv2::ImageFactory::checkType(img_type, *io, advance);
            io->close();
        }

        // Test open
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(file_path, useCurl);
        if (!image) {
            return 0;
        }

        // Test create (both overloads)
        try {
            Exiv2::Image::UniquePtr created_img = Exiv2::ImageFactory::create(img_type);
            Exiv2::Image::UniquePtr created_img_file = Exiv2::ImageFactory::create(img_type, file_path);
        } catch (...) {
            // Ignore create failures
        }

    } catch (const Exiv2::Error& e) {
        // Ignore Exiv2 exceptions
    } catch (...) {
        // Ignore all other exceptions
    }

    return 0;
}