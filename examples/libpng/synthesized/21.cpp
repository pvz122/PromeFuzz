// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_cHRM_fixed at pngset.c:39:1 in png.h
// png_set_pHYs at pngset.c:728:1 in png.h
// png_set_mDCV_fixed at pngset.c:225:1 in png.h
// png_get_cHRM_XYZ_fixed at pngget.c:598:1 in png.h
// png_get_cHRM_fixed at pngget.c:628:1 in png.h
// png_get_sCAL_fixed at pngget.c:1035:1 in png.h
// png_get_mDCV_fixed at pngget.c:830:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
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

    png_set_cHRM_fixed(png_ptr, info_ptr, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000);
    png_set_pHYs(png_ptr, info_ptr, 72, 72, PNG_RESOLUTION_METER);
    png_set_mDCV_fixed(png_ptr, info_ptr, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 50000, 100000, 10000);

    png_fixed_point int_red_X, int_red_Y, int_red_Z;
    png_fixed_point int_green_X, int_green_Y, int_green_Z;
    png_fixed_point int_blue_X, int_blue_Y, int_blue_Z;
    png_get_cHRM_XYZ_fixed(png_ptr, info_ptr, &int_red_X, &int_red_Y, &int_red_Z, &int_green_X, &int_green_Y, &int_green_Z, &int_blue_X, &int_blue_Y, &int_blue_Z);

    png_fixed_point int_white_x, int_white_y;
    png_fixed_point int_red_x, int_red_y;
    png_fixed_point int_green_x, int_green_y;
    png_fixed_point int_blue_x, int_blue_y;
    png_get_cHRM_fixed(png_ptr, info_ptr, &int_white_x, &int_white_y, &int_red_x, &int_red_y, &int_green_x, &int_green_y, &int_blue_x, &int_blue_y);

    int unit;
    png_fixed_point width, height;
    png_get_sCAL_fixed(png_ptr, info_ptr, &unit, &width, &height);

    png_uint_32 mastering_display_maximum_luminance_scaled_by_10000, mastering_display_minimum_luminance_scaled_by_10000;
    png_get_mDCV_fixed(png_ptr, info_ptr, &int_white_x, &int_white_y, &int_red_x, &int_red_y, &int_green_x, &int_green_y, &int_blue_x, &int_blue_y, &mastering_display_maximum_luminance_scaled_by_10000, &mastering_display_minimum_luminance_scaled_by_10000);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}