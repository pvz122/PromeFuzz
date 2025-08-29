// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_read_user_chunk_fn at pngset.c:1694:1 in png.h
// png_get_user_chunk_ptr at pngget.c:1283:1 in png.h
// png_get_io_ptr at png.c:686:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_set_write_fn at pngwio.c:121:1 in png.h
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

static void dummy_write_data(png_structp png_ptr, png_bytep data, png_size_t length) {
    // Do nothing
}

static void dummy_flush_data(png_structp png_ptr) {
    // Do nothing
}

static int dummy_user_chunk_callback(png_structp png_ptr, png_unknown_chunkp chunk) {
    return 0;
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_set_read_user_chunk_fn(png_ptr, nullptr, dummy_user_chunk_callback);
    png_get_user_chunk_ptr(png_ptr);
    png_get_io_ptr(png_ptr);
    png_get_error_ptr(png_ptr);

    png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (write_ptr) {
        png_set_write_fn(write_ptr, nullptr, dummy_write_data, dummy_flush_data);
        png_destroy_write_struct(&write_ptr, nullptr);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}