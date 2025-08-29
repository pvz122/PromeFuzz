// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_tRNS at pngset.c:1149:1 in png.h
// png_get_bKGD at pngget.c:502:1 in png.h
// png_set_bKGD at pngset.c:24:1 in png.h
// png_get_tRNS at pngget.c:1213:1 in png.h
// png_set_invert_mono at pngtrans.c:249:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_set_tRNS(png_ptr, info_ptr, reinterpret_cast<png_const_bytep>(Data), Size % 256, nullptr);

    png_color_16p background;
    png_get_bKGD(png_ptr, info_ptr, &background);

    png_color_16 bg_color = {0, 0, 0, 0, 0};
    png_set_bKGD(png_ptr, info_ptr, &bg_color);

    png_bytep trans_alpha;
    int num_trans;
    png_color_16p trans_color;
    png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, &trans_color);

    png_set_invert_mono(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}