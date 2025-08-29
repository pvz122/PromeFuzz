// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_cLLI_fixed at pngset.c:162:1 in png.h
// png_get_cLLI_fixed at pngget.c:789:1 in png.h
// png_get_user_height_max at pngget.c:1322:1 in png.h
// png_get_cLLI at pngget.c:809:1 in png.h
// png_get_x_pixels_per_inch at pngget.c:363:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(png_uint_32)) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_uint_32 maxCLL = *reinterpret_cast<const png_uint_32*>(Data);
    png_uint_32 maxFALL = *reinterpret_cast<const png_uint_32*>(Data + sizeof(png_uint_32));

    png_set_cLLI_fixed(png_ptr, info_ptr, maxCLL, maxFALL);

    png_uint_32 ret_cLLI_fixed = png_get_cLLI_fixed(png_ptr, info_ptr, &maxCLL, &maxFALL);

    png_uint_32 user_height_max = png_get_user_height_max(png_ptr);

    double maxCLL_double, maxFALL_double;
    png_uint_32 ret_cLLI = png_get_cLLI(png_ptr, info_ptr, &maxCLL_double, &maxFALL_double);

    png_uint_32 x_pixels_per_inch = png_get_x_pixels_per_inch(png_ptr, info_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}