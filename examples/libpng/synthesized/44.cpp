// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_image_begin_read_from_memory at pngread.c:1429:12 in png.h
// png_create_read_struct at pngread.c:24:1 in png.h
// png_image_free at png.c:4016:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_free at png.c:4016:1 in png.h
// png_set_scale_16 at pngrtran.c:182:1 in png.h
// png_read_end at pngread.c:673:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_free at png.c:4016:1 in png.h
// png_image_finish_read at pngread.c:3975:1 in png.h
// png_image_write_to_memory at pngwrite.c:2266:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_free at png.c:4016:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_image image;
    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_memory(&image, Data, Size) == 0) {
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        png_image_free(&image);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        png_image_free(&image);
        return 0;
    }

    png_set_scale_16(png_ptr);

    png_read_end(png_ptr, info_ptr);

    png_color background = {0, 0, 0};
    void *buffer = malloc(PNG_IMAGE_SIZE(image));
    if (!buffer) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        png_image_free(&image);
        return 0;
    }

    png_image_finish_read(&image, &background, buffer, 0, nullptr);

    png_alloc_size_t memory_bytes = 0;
    png_image_write_to_memory(&image, nullptr, &memory_bytes, 0, buffer, 0, nullptr);

    free(buffer);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    png_image_free(&image);

    return 0;
}