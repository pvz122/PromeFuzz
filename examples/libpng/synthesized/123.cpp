// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_swap_alpha at pngtrans.c:222:1 in png.h
// png_set_packswap at pngtrans.c:69:1 in png.h
// png_set_expand_16 at pngrtran.c:996:1 in png.h
// png_set_gray_to_rgb at pngrtran.c:1009:1 in png.h
// png_set_bgr at pngtrans.c:20:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Use the first byte to determine which function to call
    uint8_t function_selector = Data[0] % 5;

    switch (function_selector) {
        case 0:
            png_set_swap_alpha(png_ptr);
            break;
        case 1:
            png_set_packswap(png_ptr);
            break;
        case 2:
            png_set_expand_16(png_ptr);
            break;
        case 3:
            png_set_gray_to_rgb(png_ptr);
            break;
        case 4:
            png_set_bgr(png_ptr);
            break;
        default:
            break;
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}