// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sig_bytes at png.c:53:1 in png.h
// png_set_rgb_to_gray_fixed at pngrtran.c:1024:1 in png.h
// png_set_filter_heuristics_fixed at pngwrite.c:1189:1 in png.h
// png_set_filter at pngwrite.c:1046:1 in png.h
// png_set_check_for_invalid_index at pngset.c:1888:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0; // Ensure enough data for all operations

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

    // Fuzz png_set_sig_bytes
    int num_bytes = Data[0] % 9; // Ensure num_bytes is between 0 and 8
    png_set_sig_bytes(png_ptr, num_bytes);

    // Fuzz png_set_rgb_to_gray_fixed
    int error_action = Data[1] % 3; // 0, 1, or 2
    png_fixed_point red = static_cast<png_fixed_point>(Data[2] * 100000);
    png_fixed_point green = static_cast<png_fixed_point>(Data[3] * 100000);
    png_set_rgb_to_gray_fixed(png_ptr, error_action, red, green);

    // Fuzz png_set_filter_heuristics_fixed
    int heuristic_method = Data[4] % 4; // 0, 1, 2, or 3
    int num_weights = Data[5] % 10;
    png_fixed_point filter_weights[10];
    png_fixed_point filter_costs[10];
    for (int i = 0; i < num_weights; ++i) {
        filter_weights[i] = static_cast<png_fixed_point>(Data[6 + i] * 100000);
        filter_costs[i] = static_cast<png_fixed_point>(Data[6 + num_weights + i] * 100000);
    }
    png_set_filter_heuristics_fixed(png_ptr, heuristic_method, num_weights, filter_weights, filter_costs);

    // Fuzz png_set_filter
    int method = 0; // Only valid value
    int filters = Data[Size - 1] % 256; // Random filter value
    png_set_filter(png_ptr, method, filters);

    // Fuzz png_set_check_for_invalid_index
    int allowed = Data[Size - 2] % 2 == 0 ? 1 : -1;
    png_set_check_for_invalid_index(png_ptr, allowed);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}