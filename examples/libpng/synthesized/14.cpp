// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sRGB_gAMA_and_cHRM at pngset.c:836:1 in png.h
// png_get_gAMA_fixed at pngget.c:658:1 in png.h
// png_set_sRGB at pngset.c:824:1 in png.h
// png_get_y_offset_microns at pngget.c:264:1 in png.h
// png_set_cHRM_fixed at pngset.c:39:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    int srgb_intent = Data[0] % 4;
    png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, srgb_intent);

    png_fixed_point int_file_gamma;
    png_get_gAMA_fixed(png_ptr, info_ptr, &int_file_gamma);

    png_set_sRGB(png_ptr, info_ptr, srgb_intent);

    png_get_y_offset_microns(png_ptr, info_ptr);

    png_set_cHRM_fixed(png_ptr, info_ptr, 0, 0, 0, 0, 0, 0, 0, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}