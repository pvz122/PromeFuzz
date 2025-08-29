// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_save_uint_32 at pngwutil.c:41:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_chunk_warning at pngerror.c:497:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_get_iCCP at pngget.c:718:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
// png_save_uint_16 at pngwutil.c:54:1 in png.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <png.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Test png_save_uint_32
    png_byte buf32[4];
    png_save_uint_32(buf32, *reinterpret_cast<const png_uint_32*>(Data));

    // Test png_chunk_warning
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr) {
        png_chunk_warning(png_ptr, "Test warning message");
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    } else {
        png_chunk_warning(nullptr, "Test warning message without png_ptr");
    }

    // Test png_get_uint_32
    png_uint_32 value = png_get_uint_32(reinterpret_cast<const png_byte*>(Data));

    // Test png_get_iCCP
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr) {
        png_charpp name = nullptr;
        int compression_type = 0;
        png_bytepp profile = nullptr;
        png_uint_32 proflen = 0;
        png_get_iCCP(png_ptr, info_ptr, name, &compression_type, profile, &proflen);
        png_destroy_info_struct(png_ptr, &info_ptr);
    }

    // Test png_save_uint_16
    png_byte buf16[2];
    png_save_uint_16(buf16, static_cast<unsigned int>(value & 0xFFFF));

    return 0;
}