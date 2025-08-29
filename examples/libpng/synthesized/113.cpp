// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_sRGB_gAMA_and_cHRM at pngset.c:836:1 in png.h
// png_get_x_offset_inches at pngget.c:413:1 in png.h
// png_get_y_offset_inches at pngget.c:424:1 in png.h
// png_get_oFFs at pngget.c:984:1 in png.h
// png_get_y_offset_microns at pngget.c:264:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_set_sRGB_gAMA_and_cHRM
    png_set_sRGB_gAMA_and_cHRM(png_ptr, info_ptr, Data[0] % 4);

    // Fuzz png_get_x_offset_inches
    float x_offset_inches = png_get_x_offset_inches(png_ptr, info_ptr);

    // Fuzz png_get_y_offset_inches
    float y_offset_inches = png_get_y_offset_inches(png_ptr, info_ptr);

    // Fuzz png_get_oFFs
    png_int_32 offset_x, offset_y;
    int unit_type;
    png_get_oFFs(png_ptr, info_ptr, &offset_x, &offset_y, &unit_type);

    // Fuzz png_get_y_offset_microns
    png_int_32 y_offset_microns = png_get_y_offset_microns(png_ptr, info_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}