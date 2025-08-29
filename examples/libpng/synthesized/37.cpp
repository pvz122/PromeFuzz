// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_palette_max at pngget.c:1360:1 in png.h
// png_get_sPLT at pngget.c:746:1 in png.h
// png_set_sPLT at pngset.c:1220:1 in png.h
// png_set_PLTE at pngset.c:744:1 in png.h
// png_set_invalid at pngset.c:1791:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
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

    // Fuzz png_get_palette_max
    int palette_max = png_get_palette_max(png_ptr, info_ptr);

    // Fuzz png_get_sPLT
    png_sPLT_tp entries;
    int num_splt = png_get_sPLT(png_ptr, info_ptr, &entries);

    // Fuzz png_set_sPLT
    png_sPLT_t splt;
    splt.name = (png_charp)"dummy";
    splt.depth = 8;
    splt.entries = nullptr;
    splt.nentries = 0;
    png_set_sPLT(png_ptr, info_ptr, &splt, 1);

    // Fuzz png_set_PLTE
    png_color palette[1];
    palette[0].red = 0;
    palette[0].green = 0;
    palette[0].blue = 0;
    png_set_PLTE(png_ptr, info_ptr, palette, 1);

    // Fuzz png_set_invalid
    png_set_invalid(png_ptr, info_ptr, PNG_INFO_PLTE);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}