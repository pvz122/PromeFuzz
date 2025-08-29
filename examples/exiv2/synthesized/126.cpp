// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::byteSwap8 at image.cpp:270:17 in image.hpp
// Exiv2::hexdump at types.cpp:454:6 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::good at image.cpp:725:13 in image.hpp
// Exiv2::BmffImage::parseCr3Preview at bmffimage.cpp:669:17 in bmffimage.hpp
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

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    try {
        // Create DataBuf from input
        Exiv2::DataBuf buf(Data, Size);

        // Test DataBuf::data()
        if (Size > 0) {
            Exiv2::byte* data_ptr = buf.data();
            if (Size > 20) {
                size_t offset = Size % 10;
                if (offset < Size) {
                    data_ptr = buf.data(offset);
                }
            }
        }

        // Test Image::byteSwap8
        if (Size >= 8) {
            size_t offset = Size % (Size - 7);
            bool bSwap = Size % 2;
            uint64_t swapped = Exiv2::Image::byteSwap8(buf, offset, bSwap);
        }

        // Test hexdump
        if (Size > 0) {
            std::ostringstream oss;
            size_t len = std::min((size_t)100, Size);
            size_t offset = Size % 50;
            Exiv2::hexdump(oss, buf.data(), len, offset);
        }

        // Create a dummy file for BmffImage operations
        const std::string dummy_file = "./dummy_file";
        {
            std::ofstream out(dummy_file, std::ios::binary);
            if (out.is_open()) {
                out.write(reinterpret_cast<const char*>(Data), Size);
                out.close();
            } else {
                return 0;
            }
        }

        // Test BmffImage functions
        auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::FileIo(dummy_file));
        if (io->open() != 0) {
            std::remove(dummy_file.c_str());
            return 0;
        }

        Exiv2::BmffImage image(std::move(io), false);
        if (!image.good()) {
            std::remove(dummy_file.c_str());
            return 0;
        }

        // Test parseCr3Preview with safe parameters
        if (Size >= 20) {
            std::ostringstream out_stream;
            bool bTrace = Size % 3;
            uint8_t version = Size % 256;
            size_t width_offset = Size % 5;
            size_t height_offset = Size % 7;
            size_t size_offset = Size % 9;
            size_t relative_position = Size % 11;
            
            // Ensure offsets are within bounds
            if (width_offset < Size && height_offset < Size && size_offset < Size) {
                image.parseCr3Preview(buf, out_stream, bTrace, version, width_offset,
                                    height_offset, size_offset, relative_position);
            }
        }

        // Clean up
        std::remove(dummy_file.c_str());
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}