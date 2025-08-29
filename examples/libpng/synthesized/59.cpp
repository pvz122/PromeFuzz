// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_set_expand_gray_1_2_4_to_8 at pngrtran.c:968:1 in png.h
// png_set_rgb_to_gray at pngrtran.c:1096:1 in png.h
// png_set_gamma at pngrtran.c:912:1 in png.h
// png_set_sCAL at pngset.c:669:1 in png.h
// png_set_strip_16 at pngrtran.c:196:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
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

    // Use a dummy file for fuzzing
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (!dummy_file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    dummy_file = fopen("./dummy_file", "rb");
    if (!dummy_file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_init_io(png_ptr, dummy_file);

    // Read the PNG header first
    png_read_info(png_ptr, info_ptr);

    // Fuzz target functions
    png_set_expand_gray_1_2_4_to_8(png_ptr);
    png_set_rgb_to_gray(png_ptr, 1, 0.2126, 0.7152);
    png_set_gamma(png_ptr, 2.2, 1.0);
    png_set_sCAL(png_ptr, info_ptr, PNG_SCALE_METER, 1.0, 1.0);
    png_set_strip_16(png_ptr);

    fclose(dummy_file);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}