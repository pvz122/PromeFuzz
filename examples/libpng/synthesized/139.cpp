// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_rgb_to_gray_status at pngget.c:1275:1 in png.h
// png_get_cICP at pngget.c:763:1 in png.h
// png_save_uint_32 at pngwutil.c:41:1 in png.h
// png_get_sPLT at pngget.c:746:1 in png.h
// png_get_iCCP at pngget.c:718:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_139(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize png_struct and png_info
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_get_rgb_to_gray_status
    png_byte rgb_to_gray_status = png_get_rgb_to_gray_status(png_ptr);

    // Fuzz png_get_cICP
    png_byte colour_primaries, transfer_function, matrix_coefficients, video_full_range_flag;
    png_uint_32 cicp_status = png_get_cICP(png_ptr, info_ptr, &colour_primaries, &transfer_function, &matrix_coefficients, &video_full_range_flag);

    // Fuzz png_save_uint_32
    png_byte buf[4];
    png_save_uint_32(buf, static_cast<png_uint_32>(Size));

    // Fuzz png_get_sPLT
    png_sPLT_tpp entries = nullptr;
    int splt_count = png_get_sPLT(png_ptr, info_ptr, entries);

    // Fuzz png_get_iCCP
    png_charp name;
    int compression_type;
    png_bytep profile;
    png_uint_32 proflen;
    png_uint_32 iccp_status = png_get_iCCP(png_ptr, info_ptr, &name, &compression_type, &profile, &proflen);

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}