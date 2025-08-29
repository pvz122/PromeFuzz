// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_malloc at pngmem.c:169:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_infop end_info_ptr = png_create_info_struct(png_ptr);
    if (!end_info_ptr) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    void *ptr = png_malloc(png_ptr, Size);
    if (!ptr) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
        return 0;
    }

    png_free(png_ptr, ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info_ptr);
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);
    png_destroy_read_struct(nullptr, nullptr, nullptr);

    return 0;
}