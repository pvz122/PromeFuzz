// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpParser::initialize at xmp.cpp:512:17 in xmp_exiv2.hpp
// Exiv2::ImageFactory::createIo at image.cpp:812:34 in image.hpp
// Exiv2::ImageFactory::getType at image.cpp:786:25 in image.hpp
// Exiv2::ImageFactory::open at image.cpp:847:32 in image.hpp
// Exiv2::ImageFactory::checkType at image.cpp:780:20 in image.hpp
// Exiv2::ImageFactory::create at image.cpp:886:32 in image.hpp
// Exiv2::ImageFactory::create at image.cpp:909:32 in image.hpp
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_295(const uint8_t *Data, size_t Size) {
    static bool initialized = false;
    if (!initialized) {
        Exiv2::XmpParser::initialize();
        ::atexit(Exiv2::XmpParser::terminate);
        initialized = true;
    }

    if (Size < 1) {
        return 0;
    }

    std::string file_path = "./dummy_file";
    std::ofstream out_file(file_path, std::ios::binary);
    if (!out_file.is_open()) {
        return 0;
    }
    out_file.write(reinterpret_cast<const char*>(Data), Size);
    out_file.close();

    try {
        // Test createIo
        bool useCurl = Data[0] % 2;
        Exiv2::BasicIo::UniquePtr io = Exiv2::ImageFactory::createIo(file_path, useCurl);

        // Test getType
        Exiv2::ImageType type = Exiv2::ImageFactory::getType(file_path);

        // Test open
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(file_path, useCurl);
        if (image.get() != nullptr) {
            image->readMetadata();
        }

        // Test checkType
        if (io.get() != nullptr) {
            bool advance = Data[0] % 2;
            Exiv2::ImageFactory::checkType(type, *io, advance);
        }

        // Test create (both overloads)
        if (type != Exiv2::ImageType::none) {
            Exiv2::Image::UniquePtr createdImage = Exiv2::ImageFactory::create(type, file_path);
            Exiv2::Image::UniquePtr createdImage2 = Exiv2::ImageFactory::create(type, std::move(io));
        }

    } catch (const Exiv2::Error& e) {
        // Ignore all Exiv2 exceptions
    } catch (...) {
        // Ignore all other exceptions
    }

    return 0;
}