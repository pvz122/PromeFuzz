// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_alpha_mode at pngrtran.c:455:1 in png.h
// png_set_background at pngrtran.c:166:1 in png.h
// png_set_background_fixed at pngrtran.c:136:1 in png.h
// png_set_alpha_mode_fixed at pngrtran.c:355:1 in png.h
// png_set_gamma_fixed at pngrtran.c:870:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
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

    png_color_16 background_color = {0, 0, 0, 0, 0};
    png_fixed_point output_gamma = PNG_FP_1;
    png_fixed_point screen_gamma = PNG_FP_1;
    png_fixed_point override_file_gamma = PNG_FP_1;

    int mode = Data[0] % 4;
    int background_gamma_code = Data[0] % 4;
    int need_expand = Data[0] % 2;

    png_set_alpha_mode(png_ptr, mode, PNG_DEFAULT_sRGB);
    png_set_background(png_ptr, &background_color, background_gamma_code, need_expand, 1.0);
    png_set_background_fixed(png_ptr, &background_color, background_gamma_code, need_expand, output_gamma);
    png_set_alpha_mode_fixed(png_ptr, mode, output_gamma);
    png_set_gamma_fixed(png_ptr, screen_gamma, override_file_gamma);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}