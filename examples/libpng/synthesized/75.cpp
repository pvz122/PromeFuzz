// This fuzz driver is generated for library libpng, aiming to fuzz the following functions:
// png_create_read_struct at pngread.c:24:1 in png.h
// png_create_info_struct at png.c:361:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_set_longjmp_fn at pngerror.c:597:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_init_io at png.c:703:1 in png.h
// png_read_info at pngread.c:91:1 in png.h
// png_set_expand at pngrtran.c:926:1 in png.h
// png_set_gray_to_rgb at pngrtran.c:1009:1 in png.h
// png_read_update_info at pngread.c:170:1 in png.h
// png_get_rowbytes at pngget.c:40:1 in png.h
// png_destroy_read_struct at pngread.c:825:1 in png.h
// png_read_row at pngread.c:286:1 in png.h
// png_get_current_pass_number at pngtrans.c:859:1 in png.h
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

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    fp = fopen("./dummy_file", "rb");
    if (!fp) return 0;

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(fp);
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        fclose(fp);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        return 0;
    }

    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);

    png_set_expand(png_ptr);
    png_set_gray_to_rgb(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    png_bytep row = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
    if (!row) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        return 0;
    }

    png_read_row(png_ptr, row, nullptr);
    png_byte pass_number = png_get_current_pass_number(png_ptr);

    free(row);
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);

    return 0;
}