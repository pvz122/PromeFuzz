// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_flush at pngwrite.c:954:1 in png.h
// png_set_compression_level at pngwrite.c:1204:1 in png.h
// png_set_compression_mem_level at pngwrite.c:1215:1 in png.h
// png_set_text_compression_mem_level at pngwrite.c:1303:1 in png.h
// png_set_text_compression_method at pngwrite.c:1351:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    int nrows = static_cast<int>(Data[0]);
    png_set_flush(png_ptr, nrows);

    int level = static_cast<int>(Data[0] % 10);
    png_set_compression_level(png_ptr, level);

    int mem_level = static_cast<int>(Data[0] % 9) + 1;
    png_set_compression_mem_level(png_ptr, mem_level);

    int text_mem_level = static_cast<int>(Data[0] % 9) + 1;
    png_set_text_compression_mem_level(png_ptr, text_mem_level);

    int method = static_cast<int>(Data[0] % 9) + 1;
    png_set_text_compression_method(png_ptr, method);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return 0;
}