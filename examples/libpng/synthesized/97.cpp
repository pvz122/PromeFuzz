// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_gAMA at pngset.c:377:1 in png.h
// png_set_cHRM_XYZ at pngset.c:115:1 in png.h
// png_write_info_before_PLTE at pngwrite.c:83:1 in png.h
// png_get_cHRM_XYZ at pngget.c:559:1 in png.h
// png_read_update_info at pngread.c:170:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    double gamma = static_cast<double>(Data[0]) / 255.0;
    png_set_gAMA(png_ptr, info_ptr, gamma);

    double red_X = static_cast<double>(Data[1]) / 255.0;
    double red_Y = static_cast<double>(Data[2]) / 255.0;
    double red_Z = static_cast<double>(Data[3]) / 255.0;
    double green_X = static_cast<double>(Data[4]) / 255.0;
    double green_Y = static_cast<double>(Data[5]) / 255.0;
    double green_Z = static_cast<double>(Data[6]) / 255.0;
    double blue_X = static_cast<double>(Data[7]) / 255.0;
    double blue_Y = static_cast<double>(Data[8]) / 255.0;
    double blue_Z = static_cast<double>(Data[9]) / 255.0;
    png_set_cHRM_XYZ(png_ptr, info_ptr, red_X, red_Y, red_Z, green_X, green_Y, green_Z, blue_X, blue_Y, blue_Z);

    png_write_info_before_PLTE(png_ptr, info_ptr);

    double retrieved_red_X, retrieved_red_Y, retrieved_red_Z;
    double retrieved_green_X, retrieved_green_Y, retrieved_green_Z;
    double retrieved_blue_X, retrieved_blue_Y, retrieved_blue_Z;
    png_get_cHRM_XYZ(png_ptr, info_ptr, &retrieved_red_X, &retrieved_red_Y, &retrieved_red_Z, &retrieved_green_X, &retrieved_green_Y, &retrieved_green_Z, &retrieved_blue_X, &retrieved_blue_Y, &retrieved_blue_Z);

    png_read_update_info(png_ptr, info_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}