// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct_2 at pngread.c:39:1 in png.h
// png_get_chunk_malloc_max at pngget.c:1336:1 in png.h
// png_set_chunk_malloc_max at pngset.c:1829:1 in png.h
// png_malloc at pngmem.c:169:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_image_write_to_memory at pngwrite.c:2266:1 in png.h
// png_free at pngmem.c:230:1 in png.h
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

static void dummy_error_fn(png_structp, png_const_charp) {}
static void dummy_warning_fn(png_structp, png_const_charp) {}
static png_voidp dummy_malloc_fn(png_structp, png_alloc_size_t size) { return malloc(size); }
static void dummy_free_fn(png_structp, png_voidp ptr) { free(ptr); }

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct_2(
        PNG_LIBPNG_VER_STRING, nullptr, dummy_error_fn, dummy_warning_fn,
        nullptr, dummy_malloc_fn, dummy_free_fn);
    if (!png_ptr) return 0;

    png_alloc_size_t chunk_malloc_max = png_get_chunk_malloc_max(png_ptr);
    png_set_chunk_malloc_max(png_ptr, chunk_malloc_max + (Data[0] % 256));

    png_voidp mem = png_malloc(png_ptr, Size);
    if (!mem) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }
    memcpy(mem, Data, Size);

    png_image image;
    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;
    image.width = 1;  // Set a valid width to avoid division by zero
    image.height = 1; // Set a valid height to avoid division by zero
    image.format = PNG_FORMAT_RGBA;

    png_alloc_size_t memory_bytes = 0;
    if (Size >= 4) {
        png_image_write_to_memory(&image, nullptr, &memory_bytes, 0, mem, 0, nullptr);
    }

    png_free(png_ptr, mem);
    png_destroy_read_struct(&png_ptr, nullptr, nullptr);

    return 0;
}