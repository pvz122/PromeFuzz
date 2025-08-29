// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_cHRM_XYZ_fixed at pngset.c:62:1 in png.h
// png_get_x_offset_inches_fixed at pngget.c:393:1 in png.h
// png_get_x_offset_microns at pngget.c:244:1 in png.h
// png_get_y_offset_inches_fixed at pngget.c:403:1 in png.h
// png_set_sCAL_fixed at pngset.c:699:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

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

    png_fixed_point red_X = 0, red_Y = 0, red_Z = 0;
    png_fixed_point green_X = 0, green_Y = 0, green_Z = 0;
    png_fixed_point blue_X = 0, blue_Y = 0, blue_Z = 0;

    png_set_cHRM_XYZ_fixed(png_ptr, info_ptr, red_X, red_Y, red_Z, green_X, green_Y, green_Z, blue_X, blue_Y, blue_Z);

    png_fixed_point x_offset_inches = png_get_x_offset_inches_fixed(png_ptr, info_ptr);

    png_int_32 x_offset_microns = png_get_x_offset_microns(png_ptr, info_ptr);

    png_fixed_point y_offset_inches = png_get_y_offset_inches_fixed(png_ptr, info_ptr);

    png_set_sCAL_fixed(png_ptr, info_ptr, 0, 0, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}