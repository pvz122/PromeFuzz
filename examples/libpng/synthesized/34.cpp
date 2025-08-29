// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_compression_buffer_size at pngget.c:1290:1 in png.h
// png_malloc_default at pngmem.c:186:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_malloc_warn at pngmem.c:209:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_get_mem_ptr at pngmem.c:274:1 in png.h
// png_get_error_ptr at pngerror.c:856:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    // Fuzz png_get_compression_buffer_size
    size_t buffer_size = png_get_compression_buffer_size(png_ptr);

    // Fuzz png_malloc_default
    png_voidp mem_default = png_malloc_default(png_ptr, Size);
    if (mem_default) {
        memcpy(mem_default, Data, Size);
        png_free(png_ptr, mem_default);
    }

    // Fuzz png_malloc_warn
    png_voidp mem_warn = png_malloc_warn(png_ptr, Size);
    if (mem_warn) {
        memcpy(mem_warn, Data, Size);
        png_free(png_ptr, mem_warn);
    }

    // Fuzz png_get_mem_ptr
    png_voidp mem_ptr = png_get_mem_ptr(png_ptr);

    // Fuzz png_get_error_ptr
    png_voidp error_ptr = png_get_error_ptr(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}