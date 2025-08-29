// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_swap_alpha at pngtrans.c:222:1 in png.h
// png_get_pHYs at pngget.c:1098:1 in png.h
// png_set_add_alpha at pngtrans.c:204:1 in png.h
// png_set_filler at pngtrans.c:119:1 in png.h
// png_set_palette_to_rgb at pngrtran.c:956:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_set_swap_alpha
    png_set_swap_alpha(png_ptr);

    // Fuzz png_get_pHYs
    png_uint_32 res_x, res_y;
    int unit_type;
    png_get_pHYs(png_ptr, info_ptr, &res_x, &res_y, &unit_type);

    // Fuzz png_set_add_alpha
    png_set_add_alpha(png_ptr, Data[0] % 256, PNG_FILLER_AFTER);

    // Fuzz png_set_filler
    png_set_filler(png_ptr, Data[0] % 256, PNG_FILLER_AFTER);

    // Fuzz png_set_palette_to_rgb
    png_set_palette_to_rgb(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}