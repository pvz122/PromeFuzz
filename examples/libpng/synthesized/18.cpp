// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sRGB at pngset.c:824:1 in png.h
// png_get_palette_max at pngget.c:1360:1 in png.h
// png_get_x_offset_inches_fixed at pngget.c:393:1 in png.h
// png_set_PLTE at pngset.c:744:1 in png.h
// png_set_gAMA_fixed at pngset.c:363:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
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

    // Fuzz png_set_sRGB
    png_set_sRGB(png_ptr, info_ptr, Data[0] % 4);

    // Fuzz png_get_palette_max
    png_get_palette_max(png_ptr, info_ptr);

    // Fuzz png_get_x_offset_inches_fixed
    png_get_x_offset_inches_fixed(png_ptr, info_ptr);

    // Fuzz png_set_PLTE
    png_color palette[256];
    for (int i = 0; i < 256; ++i) {
        palette[i].red = Data[i % Size];
        palette[i].green = Data[(i + 1) % Size];
        palette[i].blue = Data[(i + 2) % Size];
    }
    png_set_PLTE(png_ptr, info_ptr, palette, Data[0] % 256);

    // Fuzz png_set_gAMA_fixed
    png_set_gAMA_fixed(png_ptr, info_ptr, static_cast<png_fixed_point>(Data[0]));

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}