// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sRGB_gAMA_and_cHRM at pngset.c:836:1 in png.h
// png_get_cHRM_XYZ at pngget.c:559:1 in png.h
// png_set_mDCV at pngset.c:297:1 in png.h
// png_get_mDCV at pngget.c:861:1 in png.h
// png_get_gAMA at pngget.c:677:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_set_sRGB_gAMA_and_cHRM
    png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, Data[0] % 4);

    // Fuzz png_get_cHRM_XYZ
    double red_X, red_Y, red_Z, green_X, green_Y, green_Z, blue_X, blue_Y, blue_Z;
    png_get_cHRM_XYZ(png_ptr, info_ptr, &red_X, &red_Y, &red_Z, &green_X, &green_Y, &green_Z, &blue_X, &blue_Y, &blue_Z);

    // Fuzz png_set_mDCV
    png_set_mDCV(png_ptr, info_ptr, 0.3127, 0.3290, 0.64, 0.33, 0.3, 0.6, 0.15, 0.06, 1000.0, 0.1);

    // Fuzz png_get_mDCV
    double white_x, white_y, red_x, red_y, green_x, green_y, blue_x, blue_y, max_lum, min_lum;
    png_get_mDCV(png_ptr, info_ptr, &white_x, &white_y, &red_x, &red_y, &green_x, &green_y, &blue_x, &blue_y, &max_lum, &min_lum);

    // Fuzz png_get_gAMA
    double file_gamma;
    png_get_gAMA(png_ptr, info_ptr, &file_gamma);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}