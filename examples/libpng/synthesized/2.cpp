// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_begin_read_from_memory at pngread.c:1429:12 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_read_row at pngread.c:286:1 in png.h
// png_read_end at pngread.c:673:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_finish_read at pngread.c:3975:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

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

    png_image image;
    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_memory(&image, Data, Size) == 0) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    png_bytep row = (png_bytep)malloc(rowbytes);
    if (!row) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_read_row(png_ptr, row, nullptr);
    png_read_end(png_ptr, info_ptr);

    png_color background = {0, 0, 0};
    png_bytep buffer = (png_bytep)malloc(PNG_IMAGE_SIZE(image));
    if (!buffer) {
        free(row);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_image_finish_read(&image, &background, buffer, 0, nullptr);

    free(buffer);
    free(row);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}