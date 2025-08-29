// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Image::byteSwap8 at image.cpp:270:17 in image.hpp
// Exiv2::hexdump at types.cpp:454:6 in types.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::BmffImage::parseCr3Preview at bmffimage.cpp:669:17 in bmffimage.hpp
// Exiv2::BmffImage::parseXmp at bmffimage.cpp:645:17 in bmffimage.hpp
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

extern "C" int LLVMFuzzerTestOneInput_221(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    try {
        // Create DataBuf from input
        Exiv2::DataBuf buf(Data, Size);

        // Test DataBuf::data()
        Exiv2::byte* data_ptr = buf.data();
        size_t offset = Data[0] % (Size + 1);
        if (offset < Size) {
            Exiv2::byte* offset_ptr = buf.data(offset);
        }

        // Test Image::byteSwap8
        bool bSwap = (Data[1] % 2) == 0;
        size_t byteSwapOffset = Data[2] % (Size - 7);
        if (byteSwapOffset + 8 <= Size) {
            uint64_t swapped = Exiv2::Image::byteSwap8(buf, byteSwapOffset, bSwap);
        }

        // Test hexdump
        std::ostringstream hexdump_os;
        size_t hexdump_len = Data[3] % (Size + 1);
        size_t hexdump_offset = Data[4] % (Size + 1);
        if (hexdump_len > 0 && hexdump_offset < Size) {
            Exiv2::hexdump(hexdump_os, buf.data(), std::min(hexdump_len, Size - hexdump_offset), hexdump_offset);
        }

        // Create a dummy file for BmffImage operations
        const std::string dummy_file = "./dummy_file";
        std::ofstream out(dummy_file, std::ios::binary);
        out.write(reinterpret_cast<const char*>(Data), Size);
        out.close();

        // Create BmffImage instance
        Exiv2::BasicIo::UniquePtr io(new Exiv2::FileIo(dummy_file));
        if (io->open() == 0) {
            Exiv2::BmffImage bmffImage(std::move(io), false);

            // Test parseCr3Preview with safe parameters
            if (Size > 20) {
                std::ostringstream parse_os;
                bool bTrace = (Data[5] % 2) == 0;
                uint8_t version = Data[6];
                size_t width_offset = Data[7] % (Size - 8);
                size_t height_offset = Data[8] % (Size - 8);
                size_t size_offset = Data[9] % (Size - 8);
                size_t relative_position = Data[10] % (Size - 8);
                
                if (width_offset + 4 <= Size && height_offset + 4 <= Size && size_offset + 4 <= Size) {
                    bmffImage.parseCr3Preview(buf, parse_os, bTrace, version, width_offset,
                                            height_offset, size_offset, relative_position);
                }
            }

            // Test parseXmp with safe parameters
            if (Size > 30) {
                uint64_t xmp_length = Data[11] % (Size - 20);
                uint64_t xmp_start = Data[12] % (Size - 20);
                if (xmp_start + xmp_length <= Size) {
                    bmffImage.parseXmp(xmp_length, xmp_start);
                }
            }
        }

        // Clean up
        remove(dummy_file.c_str());
    } catch (...) {
        // Catch all exceptions silently
    }

    return 0;
}