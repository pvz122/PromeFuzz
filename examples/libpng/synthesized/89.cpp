// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_build_grayscale_palette at png.c:875:1 in png.h
// png_set_tRNS at pngset.c:1149:1 in png.h
// png_set_quantize at pngrtran.c:483:1 in png.h
// png_set_option at png.c:3766:1 in png.h
// png_set_filter at pngwrite.c:1046:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize libpng structures
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_build_grayscale_palette
    int bit_depth = Data[0] % 4 + 1; // Ensure bit_depth is 1, 2, or 4
    png_color palette[256];
    png_build_grayscale_palette(bit_depth, palette);

    // Fuzz png_set_tRNS
    png_byte trans_alpha[256];
    png_color_16 trans_color;
    int num_trans = Size % 256;
    if (num_trans > 0) {
        memcpy(trans_alpha, Data, std::min(num_trans, static_cast<int>(Size)));
    }
    png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, &trans_color);

    // Fuzz png_set_quantize
    int num_palette = Size % 256;
    int maximum_colors = Size % 256;
    png_uint_16 histogram[256];
    if (Size >= sizeof(histogram)) {
        memcpy(histogram, Data, sizeof(histogram));
    } else {
        memset(histogram, 0, sizeof(histogram));
    }
    png_set_quantize(png_ptr, palette, num_palette, maximum_colors, histogram, 1);

    // Fuzz png_set_option
    int option = Data[0] % 256;
    int onoff = Data[0] % 2;
    png_set_option(png_ptr, option, onoff);

    // Fuzz png_set_filter
    int method = 0;
    int filters = Data[0] % 256;
    png_set_filter(png_ptr, method, filters);

    // Cleanup
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}