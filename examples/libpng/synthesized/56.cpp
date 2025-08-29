// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_compression_level at pngwrite.c:1204:1 in png.h
// png_set_alpha_mode_fixed at pngrtran.c:355:1 in png.h
// png_set_gamma_fixed at pngrtran.c:870:1 in png.h
// png_set_option at png.c:3766:1 in png.h
// png_set_cHRM_fixed at pngset.c:39:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < 14) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    // Fuzz png_set_compression_level
    int compression_level = Data[0] % 10;
    png_set_compression_level(png_ptr, compression_level);

    // Fuzz png_set_alpha_mode_fixed
    int mode = Data[1] % 2 ? PNG_ALPHA_PNG : PNG_ALPHA_STANDARD;
    png_fixed_point output_gamma = PNG_DEFAULT_sRGB;
    png_set_alpha_mode_fixed(png_ptr, mode, output_gamma);

    // Fuzz png_set_gamma_fixed
    png_fixed_point screen_gamma = 100000 + (Data[2] % 100000);
    png_fixed_point override_file_gamma = 100000 + (Data[3] % 100000);
    png_set_gamma_fixed(png_ptr, screen_gamma, override_file_gamma);

    // Fuzz png_set_option
    int option = Data[4] % 10;
    int onoff = Data[5] % 2;
    png_set_option(png_ptr, option, onoff);

    // Fuzz png_set_cHRM_fixed
    png_fixed_point white_x = 100000 + (Data[6] % 100000);
    png_fixed_point white_y = 100000 + (Data[7] % 100000);
    png_fixed_point red_x = 100000 + (Data[8] % 100000);
    png_fixed_point red_y = 100000 + (Data[9] % 100000);
    png_fixed_point green_x = 100000 + (Data[10] % 100000);
    png_fixed_point green_y = 100000 + (Data[11] % 100000);
    png_fixed_point blue_x = 100000 + (Data[12] % 100000);
    png_fixed_point blue_y = 100000 + (Data[13] % 100000);
    png_set_cHRM_fixed(png_ptr, info_ptr, white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return 0;
}