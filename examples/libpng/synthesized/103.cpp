// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_write_info at pngwrite.c:223:1 in png.h
// png_write_row at pngwrite.c:744:1 in png.h
// png_write_end at pngwrite.c:392:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    // Set up image dimensions and color type
    png_set_IHDR(png_ptr, info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Allocate memory for image data
    png_bytep row = (png_bytep)malloc(3);
    if (!row) {
        fclose(fp);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }
    row[0] = Data[0];
    row[1] = Data[1];
    row[2] = Data[2];

    // Write image data
    png_write_info(png_ptr, info_ptr);
    png_write_row(png_ptr, row);
    png_write_end(png_ptr, nullptr);

    free(row);
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    return 0;
}