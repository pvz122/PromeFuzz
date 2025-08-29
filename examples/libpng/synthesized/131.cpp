// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_save_int_32 at png.c:726:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_free_data at png.c:478:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_set_option at png.c:3766:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_set_filter at pngwrite.c:1046:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_set_cHRM_fixed at pngset.c:39:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(png_int_32)) return 0;

    // Test png_save_int_32
    png_byte buf[4];
    png_int_32 i;
    memcpy(&i, Data, sizeof(png_int_32));
    png_save_int_32(buf, i);

    // Test png_free_data
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (png_ptr && info_ptr) {
        png_free_data(png_ptr, info_ptr, PNG_FREE_TEXT, -1);
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    // Test png_set_option
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr) {
        png_set_option(png_ptr, 0, 1); // Use a valid option value
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    }

    // Test png_set_filter
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (png_ptr) {
        png_set_filter(png_ptr, 0, PNG_FILTER_VALUE_NONE);
        png_destroy_write_struct(&png_ptr, nullptr);
    }

    // Test png_set_cHRM_fixed
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    info_ptr = png_create_info_struct(png_ptr);
    if (png_ptr && info_ptr) {
        png_set_cHRM_fixed(png_ptr, info_ptr, 31270, 32900, 64000, 33000, 30000, 60000, 15000, 6000);
        png_destroy_write_struct(&png_ptr, &info_ptr);
    }

    return 0;
}