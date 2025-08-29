// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_get_libpng_ver at png.c:837:1 in png.h
// png_set_shift at pngtrans.c:83:1 in png.h
// png_process_data_skip at pngpread.c:92:1 in png.h
// png_get_chunk_cache_max at pngget.c:1329:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
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

    // Fuzz png_get_libpng_ver
    png_const_charp version = png_get_libpng_ver(png_ptr);

    // Fuzz png_set_shift
    png_color_8 true_bits;
    true_bits.red = Data[0];
    png_set_shift(png_ptr, &true_bits);

    // Fuzz png_process_data_skip
    png_uint_32 skip_bytes = png_process_data_skip(png_ptr);

    // Fuzz png_get_chunk_cache_max
    png_uint_32 chunk_cache_max = png_get_chunk_cache_max(png_ptr);

    // Fuzz png_get_user_width_max
    png_uint_32 user_width_max = png_get_user_width_max(png_ptr);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    return 0;
}