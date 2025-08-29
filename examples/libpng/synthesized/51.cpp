// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_read_status_fn at pngread.c:851:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_write_status_fn at pngwrite.c:1367:1 in png.h
// png_set_write_user_transform_fn at pngwrite.c:1379:1 in png.h
// png_set_palette_to_rgb at pngrtran.c:956:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_write_info at pngwrite.c:223:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_write_row at pngwrite.c:744:1 in png.h
// png_write_end at pngwrite.c:392:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

static void dummy_read_status_fn(png_structp png_ptr, png_uint_32 row, int pass) {}
static void dummy_write_status_fn(png_structp png_ptr, png_uint_32 row, int pass) {}
static void dummy_user_transform_fn(png_structp png_ptr, png_row_infop row_info, png_bytep data) {}

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_set_read_status_fn(png_ptr, dummy_read_status_fn);

    png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!write_ptr) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_infop write_info_ptr = png_create_info_struct(write_ptr);
    if (!write_info_ptr) {
        png_destroy_write_struct(&write_ptr, nullptr);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_set_write_status_fn(write_ptr, dummy_write_status_fn);
    png_set_write_user_transform_fn(write_ptr, dummy_user_transform_fn);

    png_set_palette_to_rgb(png_ptr);

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_write_struct(&write_ptr, &write_info_ptr);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    png_init_io(write_ptr, fp);

    png_set_IHDR(write_ptr, write_info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(write_ptr, write_info_ptr);

    png_bytep row = (png_bytep)malloc(3); // Allocate enough space for 1 pixel in RGB format
    if (!row) {
        fclose(fp);
        png_destroy_write_struct(&write_ptr, &write_info_ptr);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    memcpy(row, Data, std::min(Size, (size_t)3)); // Copy only up to 3 bytes

    png_write_row(write_ptr, row);
    png_write_end(write_ptr, nullptr);

    free(row);
    fclose(fp);
    png_destroy_write_struct(&write_ptr, &write_info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}