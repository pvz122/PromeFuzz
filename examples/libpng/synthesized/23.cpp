// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_malloc_warn at pngmem.c:209:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_set_chunk_malloc_max at pngset.c:1829:1 in png.h
// png_data_freer at png.c:459:1 in png.h
// png_calloc at pngmem.c:48:1 in png.h
// png_free at pngmem.c:230:1 in png.h
// png_set_compression_buffer_size at pngset.c:1729:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    // Fuzz png_malloc_warn
    size_t alloc_size = Size > 1024 ? 1024 : Size;
    void *mem = png_malloc_warn(png_ptr, alloc_size);
    if (mem) png_free(png_ptr, mem);

    // Fuzz png_set_chunk_malloc_max
    png_set_chunk_malloc_max(png_ptr, Size);

    // Fuzz png_data_freer
    int freer = Data[0] % 3; // Ensure freer is 0, 1, or 2
    png_data_freer(png_ptr, info_ptr, freer, Size);

    // Fuzz png_calloc
    void *zeroed_mem = png_calloc(png_ptr, alloc_size);
    if (zeroed_mem) png_free(png_ptr, zeroed_mem);

    // Fuzz png_set_compression_buffer_size
    png_set_compression_buffer_size(png_ptr, Size % PNG_UINT_31_MAX);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}