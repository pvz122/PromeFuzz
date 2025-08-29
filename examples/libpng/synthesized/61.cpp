// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_set_expand_gray_1_2_4_to_8 at pngrtran.c:968:1 in png.h
// png_set_scale_16 at pngrtran.c:182:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_create_write_struct at pngwrite.c:543:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_write_sig at pngwutil.c:68:1 in png.h
// png_set_packing at pngtrans.c:49:1 in png.h
// png_destroy_write_struct at pngwrite.c:1025:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

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

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return 0;
    }

    png_init_io(png_ptr, file);

    png_set_expand_gray_1_2_4_to_8(png_ptr);
    png_set_scale_16(png_ptr);
    png_read_info(png_ptr, info_ptr);

    png_structp write_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!write_ptr) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(file);
        return 0;
    }

    png_infop write_info_ptr = png_create_info_struct(write_ptr);
    if (!write_info_ptr) {
        png_destroy_write_struct(&write_ptr, nullptr);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(file);
        return 0;
    }

    if (setjmp(png_jmpbuf(write_ptr))) {
        png_destroy_write_struct(&write_ptr, &write_info_ptr);
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(file);
        return 0;
    }

    png_init_io(write_ptr, file);
    png_write_sig(write_ptr);
    png_set_packing(write_ptr);

    png_destroy_write_struct(&write_ptr, &write_info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(file);

    return 0;
}