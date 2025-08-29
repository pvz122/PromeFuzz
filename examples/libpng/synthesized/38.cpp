// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_user_limits at pngset.c:1801:1 in png.h
// png_get_user_width_max at pngget.c:1316:1 in png.h
// png_get_user_height_max at pngget.c:1322:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_set_sCAL at pngset.c:669:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(png_uint_32) * 2) return 0;

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

    png_uint_32 user_width_max = *reinterpret_cast<const png_uint_32*>(Data);
    png_uint_32 user_height_max = *reinterpret_cast<const png_uint_32*>(Data + sizeof(png_uint_32));

    png_set_user_limits(png_ptr, user_width_max, user_height_max);

    png_uint_32 retrieved_width_max = png_get_user_width_max(png_ptr);
    png_uint_32 retrieved_height_max = png_get_user_height_max(png_ptr);

    png_uint_32 width = retrieved_width_max;
    png_uint_32 height = retrieved_height_max;
    int bit_depth = 8;
    int color_type = PNG_COLOR_TYPE_RGB;
    int interlace_method = PNG_INTERLACE_NONE;
    int compression_method = PNG_COMPRESSION_TYPE_DEFAULT;
    int filter_method = PNG_FILTER_TYPE_DEFAULT;

    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_method, compression_method, filter_method);

    int unit = PNG_SCALE_METER;
    double sCAL_width = 1.0;
    double sCAL_height = 1.0;
    png_set_sCAL(png_ptr, info_ptr, unit, sCAL_width, sCAL_height);

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

    return 0;
}