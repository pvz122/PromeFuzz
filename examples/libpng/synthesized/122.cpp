// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_chunk_malloc_max at pngget.c:1336:1 in png.h
// png_get_io_state at pngget.c:1345:1 in png.h
// png_get_chunk_cache_max at pngget.c:1329:1 in png.h
// png_get_io_chunk_type at pngget.c:1351:1 in png.h
// png_get_user_width_max at pngget.c:1316:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        return 0;
    }

    png_get_chunk_malloc_max(png_ptr);
    png_get_io_state(png_ptr);
    png_get_chunk_cache_max(png_ptr);
    png_get_io_chunk_type(png_ptr);
    png_get_user_width_max(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}