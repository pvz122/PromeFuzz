// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_sRGB_gAMA_and_cHRM at pngset.c:836:1 in png.h
// png_set_gamma_fixed at pngrtran.c:870:1 in png.h
// png_set_mDCV_fixed at pngset.c:225:1 in png.h
// png_set_option at png.c:3766:1 in png.h
// png_write_png at pngwrite.c:1395:1 in png.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_85(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    // Fuzz png_set_sRGB_gAMA_and_cHRM
    png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, Data[0] % 4);

    // Fuzz png_set_gamma_fixed with valid gamma values
    png_fixed_point screen_gamma = static_cast<png_fixed_point>(Data[1] * 1000);
    png_fixed_point file_gamma = static_cast<png_fixed_point>(Data[2] * 1000);
    if (screen_gamma > 0 && file_gamma > 0) {
        png_set_gamma_fixed(png_ptr, screen_gamma, file_gamma);
    }

    // Fuzz png_set_mDCV_fixed with valid values
    png_set_mDCV_fixed(png_ptr, info_ptr,
                       static_cast<png_fixed_point>(Data[3] * 1000),
                       static_cast<png_fixed_point>(Data[4] * 1000),
                       static_cast<png_fixed_point>(Data[5] * 1000),
                       static_cast<png_fixed_point>(Data[6] * 1000),
                       static_cast<png_fixed_point>(Data[7] * 1000),
                       static_cast<png_fixed_point>(Data[8] * 1000),
                       static_cast<png_fixed_point>(Data[9] * 1000),
                       static_cast<png_fixed_point>(Data[10] * 1000),
                       static_cast<png_uint_32>(Data[11] * 1000),
                       static_cast<png_uint_32>(Data[12] * 1000));

    // Fuzz png_set_option
    png_set_option(png_ptr, Data[13] % 256, Data[14] % 2);

    // Fuzz png_write_png
    png_write_png(png_ptr, info_ptr, Data[15] % 256, nullptr);

    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}