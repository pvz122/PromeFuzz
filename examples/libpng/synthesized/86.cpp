// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_progressive_read_fn at pngpread.c:915:1 in png.h
// png_get_mem_ptr at pngmem.c:274:1 in png.h
// png_get_io_ptr at png.c:686:1 in png.h
// png_get_user_transform_ptr at pngtrans.c:836:1 in png.h
// png_get_progressive_ptr at pngpread.c:930:1 in png.h
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

static void info_callback(png_structp png_ptr, png_infop info_ptr) {}
static void row_callback(png_structp png_ptr, png_bytep new_row, png_uint_32 row_num, int pass) {}
static void end_callback(png_structp png_ptr, png_infop info_ptr) {}

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_set_progressive_read_fn(png_ptr, nullptr, info_callback, row_callback, end_callback);

    png_voidp mem_ptr = png_get_mem_ptr(png_ptr);
    png_voidp io_ptr = png_get_io_ptr(png_ptr);
    png_voidp user_transform_ptr = png_get_user_transform_ptr(png_ptr);
    png_voidp progressive_ptr = png_get_progressive_ptr(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}