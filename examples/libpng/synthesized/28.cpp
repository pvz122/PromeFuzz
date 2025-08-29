// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_sBIT at pngset.c:809:1 in png.h
// png_set_IHDR at pngset.c:429:1 in png.h
// png_write_info_before_PLTE at pngwrite.c:83:1 in png.h
// png_write_info at pngwrite.c:223:1 in png.h
// png_write_end at pngwrite.c:392:1 in png.h
// png_destroy_info_struct at png.c:394:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return 0;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_info_struct(png_ptr, &info_ptr);
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) {
        png_destroy_info_struct(png_ptr, &info_ptr);
        png_destroy_write_struct(&png_ptr, nullptr);
        return 0;
    }

    png_init_io(png_ptr, fp);

    png_color_8 sig_bit;
    sig_bit.red = Data[0] % 8;
    sig_bit.green = Data[1] % 8;
    sig_bit.blue = Data[2] % 8;
    sig_bit.alpha = Data[3] % 8;
    sig_bit.gray = Data[4] % 8;

    png_set_sBIT(png_ptr, info_ptr, &sig_bit);

    png_set_IHDR(png_ptr, info_ptr, 1, 1, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info_before_PLTE(png_ptr, info_ptr);

    png_write_info(png_ptr, info_ptr);

    png_write_end(png_ptr, info_ptr);

    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_write_struct(&png_ptr, nullptr);

    fclose(fp);

    return 0;
}