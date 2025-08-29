// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmffImage::parseCr3Preview at bmffimage.cpp:669:17 in bmffimage.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::byteSwap8 at image.cpp:270:17 in image.hpp
// Exiv2::hexdump at types.cpp:454:6 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::BasicIo::readOrThrow at basicio.cpp:55:15 in basicio.hpp
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

extern "C" int LLVMFuzzerTestOneInput_232(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        // Create a DataBuf from the input data
        Exiv2::DataBuf buf(Size);
        std::copy(Data, Data + Size, buf.data());

        // Create a dummy file for BasicIo operations
        const std::string dummy_file = "./dummy_file";
        std::ofstream out(dummy_file, std::ios::binary);
        out.write(reinterpret_cast<const char*>(Data), Size);
        out.close();

        // Initialize BasicIo with the dummy file
        Exiv2::BasicIo::UniquePtr io(new Exiv2::FileIo(dummy_file));
        if (!io->open()) {
            std::remove(dummy_file.c_str());
            return 0;
        }

        Exiv2::BmffImage image(std::move(io), false);
        if (!image.good()) {
            std::remove(dummy_file.c_str());
            return 0;
        }

        // Randomly select which function to test
        uint8_t selector = Data[0] % 5; // Reduced to 5 cases to avoid parseXmp
        
        switch (selector) {
            case 0: {
                // Test parseCr3Preview
                if (Size < 7) break;
                bool bTrace = Data[1] % 2;
                uint8_t version = Data[2];
                size_t width_offset = Data[3] % Size;
                size_t height_offset = Data[4] % Size;
                size_t size_offset = Data[5] % Size;
                size_t relative_position = Data[6] % Size;
                image.parseCr3Preview(buf, std::cout, bTrace, version, 
                                     width_offset, height_offset, 
                                     size_offset, relative_position);
                break;
            }
            case 1: {
                // Test DataBuf::data
                if (Size < 2) break;
                size_t offset = Data[1] % Size;
                buf.data(offset);
                break;
            }
            case 2: {
                // Test byteSwap8
                if (Size < 9) break;
                size_t offset = Data[1] % (Size - 8);
                bool bSwap = Data[2] % 2;
                Exiv2::Image::byteSwap8(buf, offset, bSwap);
                break;
            }
            case 3: {
                // Test hexdump
                if (Size < 3) break;
                size_t len = Data[1] % Size;
                size_t offset = Data[2] % Size;
                Exiv2::hexdump(std::cout, buf.data(), len, offset);
                break;
            }
            case 4: {
                // Test readOrThrow
                if (Size < 2) break;
                size_t rcount = Data[1] % Size;
                std::vector<Exiv2::byte> read_buf(rcount);
                image.io().readOrThrow(read_buf.data(), rcount);
                break;
            }
        }

        // Clean up the dummy file
        std::remove(dummy_file.c_str());
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}