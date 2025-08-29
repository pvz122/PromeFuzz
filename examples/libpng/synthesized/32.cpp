// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_get_PLTE at pngget.c:1132:1 in png.h
// png_get_image_height at pngget.c:71:1 in png.h
// png_get_valid at pngget.c:19:1 in png.h
// png_get_eXIf_1 at pngget.c:903:1 in png.h
// png_get_image_width at pngget.c:62:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
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

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_init_io(png_ptr, file);
    png_read_info(png_ptr, info_ptr);

    png_colorp palette;
    int num_palette;
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);

    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);

    png_uint_32 valid = png_get_valid(png_ptr, info_ptr, PNG_INFO_PLTE);

    png_uint_32 num_exif;
    png_bytep exif;
    png_get_eXIf_1(png_ptr, info_ptr, &num_exif, &exif);

    png_uint_32 width = png_get_image_width(png_ptr, info_ptr);

    fclose(file);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}