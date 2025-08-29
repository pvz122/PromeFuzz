// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_swap_alpha at pngtrans.c:222:1 in png.h
// png_set_swap at pngtrans.c:34:1 in png.h
// png_set_invert_mono at pngtrans.c:249:1 in png.h
// png_set_bgr at pngtrans.c:20:1 in png.h
// png_set_invert_alpha at pngtrans.c:236:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    uint8_t action = Data[0] % 5;

    switch (action) {
        case 0:
            png_set_swap_alpha(png_ptr);
            break;
        case 1:
            png_set_swap(png_ptr);
            break;
        case 2:
            png_set_invert_mono(png_ptr);
            break;
        case 3:
            png_set_bgr(png_ptr);
            break;
        case 4:
            png_set_invert_alpha(png_ptr);
            break;
        default:
            break;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}