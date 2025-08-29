// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_compression_method at pngwrite.c:1272:1 in png.h
// png_set_compression_window_bits at pngwrite.c:1243:1 in png.h
// png_set_compression_strategy at pngwrite.c:1226:1 in png.h
// png_set_filter at pngwrite.c:1046:1 in png.h
// png_set_text_compression_level at pngwrite.c:1292:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }

    int method = Data[0] % 10;
    int window_bits = Data[1] % 16;
    int strategy = Data[2] % 10;
    int filters = Data[3] % 256;
    int level = Data[4] % 10;

    png_set_compression_method(png_ptr, method);
    png_set_compression_window_bits(png_ptr, window_bits);
    png_set_compression_strategy(png_ptr, strategy);
    png_set_filter(png_ptr, 0, filters);
    png_set_text_compression_level(png_ptr, level);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return 0;
}